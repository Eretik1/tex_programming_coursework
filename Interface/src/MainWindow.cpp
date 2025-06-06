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
    
    chessWidget->setChessboard(gameBoard.get());
    chessWidget->setMinimumSize(600, 650);
    
    stackedWidget->addWidget(mainMenu);    
    stackedWidget->addWidget(colorMenu);   
    stackedWidget->addWidget(chessWidget); 
    
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::setupConnections()
{
    
    connect(mainMenu, &MainMenu::localGameRequested, this, [this]() {
        gameBoard = std::make_unique<chessboard>(); 
        chessWidget->setChessboard(gameBoard.get());
        stackedWidget->setCurrentIndex(1);
    });
    
    connect(colorMenu, &ColorSelectionMenu::backRequested, this, [this]() {
        stackedWidget->setCurrentIndex(0);
    });
    
    connect(colorMenu, &ColorSelectionMenu::colorSelected, this, [this](bool isWhite) {
        qDebug() << "Selected color:" << (isWhite ? "White" : "Black");
        stackedWidget->setCurrentIndex(2);
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