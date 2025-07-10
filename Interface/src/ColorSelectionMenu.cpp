#include "..\\include\\ColorSelectionMenu.h"
#include "..\\..\\network_game\\include\\GameServer.h"

#include "..\\..\\network_game\\include\\GameServer.h"
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include <iostream>

ColorSelectionMenu::ColorSelectionMenu(QWidget *parent) : QWidget(parent) {
    btnWhite = new QPushButton("Белые");
    btnBlack = new QPushButton("Чёрные");
    btnBack = new QPushButton("Назад");

    
    QString buttonStyle = "QPushButton {"
                         "    background-color: #4a4a4a;"
                         "    color: white;"
                         "    border: none;"
                         "    padding: 15px 32px;"
                         "    text-align: center;"
                         "    text-decoration: none;"
                         "    font-size: 16px;"
                         "    margin: 4px 2px;"
                         "    border-radius: 8px;"
                         "}"
                         "QPushButton:hover {"
                         "    background-color: #5a5a5a;"
                         "}";

    
    QString whiteButtonStyle = buttonStyle + 
                              "QPushButton {"
                              "    background-color:rgb(255, 255, 255);"
                              "    color: black;"
                              "}"
                              "QPushButton:hover {"
                              "    background-color:rgb(245, 245, 245);"
                              "}";

    QString blackButtonStyle = buttonStyle + 
                              "QPushButton {"
                              "    background-color: #303030;"
                              "    color: white;"
                              "}"
                              "QPushButton:hover {"
                              "    background-color: #404040;"
                              "}";

    btnWhite->setStyleSheet(whiteButtonStyle);
    btnBlack->setStyleSheet(blackButtonStyle);
    btnBack->setStyleSheet(buttonStyle);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(btnWhite);
    layout->addWidget(btnBlack);
    layout->addWidget(btnBack);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(20);

    
    this->setStyleSheet("background-color: #2d2d2d;");

    
    connect(btnWhite, &QPushButton::clicked, [this]() { 
        Server server;
        server.start(1234);
        std::cout << "Server running. Type messages to broadcast (type 'exit' to quit):\n";
        QString message;
        while (true) {
            QTextStream qtin(stdin);
            QString message = qtin.readLine();
            if (message == "exit") break;
            server.sendMessage(message);
        }
    });
    connect(btnBlack, &QPushButton::clicked, [this]() { emit colorSelected(false); });
    connect(btnBack, &QPushButton::clicked, this, &ColorSelectionMenu::backRequested);
}