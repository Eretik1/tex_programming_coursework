#include "..\\include\\MainWindow.h"
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) 
    : QWidget(parent),
      stackedWidget(new QStackedWidget(this)),
      gameBoard(std::make_unique<chessboard>())
{
    initializeWidgets();
    setupConnections();
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stackedWidget);
    setLayout(mainLayout);
}




void MainWindow::initializeWidgets()
{
    mainMenu = new MainMenu();
    colorMenu = new ColorSelectionMenu();
    chessWidget = new ChessWidget();
    intermediateMenu = new IntermediateMenu();
    ipInputMenu = new IpInputMenu();
    standbyMenu = new StandbyMenu();
    
    chessWidget->setChessboard(gameBoard.get());
    chessWidget->setMinimumSize(600, 650);
    
    stackedWidget->addWidget(mainMenu);    
    stackedWidget->addWidget(colorMenu);   
    stackedWidget->addWidget(chessWidget); 
    stackedWidget->addWidget(intermediateMenu);
    stackedWidget->addWidget(ipInputMenu);
    stackedWidget->addWidget(standbyMenu);   
    
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::setupConnections()
{
    
    connect(mainMenu, &MainMenu::localGameRequested, this, [this]() {
        gameBoard = std::make_unique<chessboard>(); 
        chessWidget->setChessboard(gameBoard.get());
        stackedWidget->setCurrentIndex(2);
    });

    connect(mainMenu, &MainMenu::onlineGameRequested, this, [this]() {
        stackedWidget->setCurrentIndex(3);
    });

    connect(intermediateMenu, &IntermediateMenu::creatingRoomRequested, this, [this]() {
        stackedWidget->setCurrentIndex(1);
    });

    connect(intermediateMenu, &IntermediateMenu::connectionRoomRequested, this, [this]() {
        stackedWidget->setCurrentIndex(4);
    });

    connect(intermediateMenu, &IntermediateMenu::backRequested, this, [this]() {
        stackedWidget->setCurrentIndex(0);
    });
    
    connect(colorMenu, &ColorSelectionMenu::backRequested, this, [this]() {
        stackedWidget->setCurrentIndex(0);
    });
    
    connect(colorMenu, &ColorSelectionMenu::colorSelected, this, [this](bool isWhite) {
        stackedWidget->setCurrentIndex(5);
        standbyMenu->connection(true);
        server = new Server(this);
        if (!server->startServer()) {
            qDebug() << "Ошибка, не удалось запустить сервер";
        }
        connect(server, &Server::newConnection, this, [this](){
            standbyMenu->connection(false);
        });
    });

    connect(ipInputMenu, &IpInputMenu::backRequested, this, [this]() {
        stackedWidget->setCurrentIndex(3);
    });

    connect(ipInputMenu, &IpInputMenu::connection, this, [this](QString IP) {
        client = new Client(this);
        if(client->connectToServer(IP, 12345)){
            stackedWidget->setCurrentIndex(5);
            standbyMenu->connection(false);
            QString message = "Hello";
            client->sendToServer(message);
            connect(client, &Client::disconnect, this, [this](){
                qDebug() << "out";
                standbyMenu->backRequested(false);
            });
        }
    });

    connect(standbyMenu, &StandbyMenu::backRequested, this, [this](bool isServer) {
        if(isServer){
            server->stopServer();
        }
        else{
            client->disconnectFromHost(); 
            client->deleteLater();
            client = nullptr;
        }
        stackedWidget->setCurrentIndex(3);
    });
    
    connect(chessWidget, &ChessWidget::cellSelected, this, [this](int x, int y) {
        qDebug() << "Cell selected:" << x << y;
    });

    connect(chessWidget, &ChessWidget::gameEndRequested, this, [this]() {
        gameBoard.reset(); 
        stackedWidget->setCurrentWidget(mainMenu);
    });
}

chessboard* MainWindow::createNewGameBoard()
{
    return new chessboard();
}