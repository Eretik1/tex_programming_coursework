#include "..\\include\\ColorSelectionMenu.h"
#include "..\\..\\network_game\\include\\GameServer.h"

#include "..\\..\\network_game\\include\\GameServer.h"
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include <iostream>
#include <QStyle>
#include <QFile>


ColorSelectionMenu::ColorSelectionMenu(QWidget *parent) : QWidget(parent) {
    btnWhite = new QPushButton("Белые");
    btnBlack = new QPushButton("Чёрные");
    btnBack = new QPushButton("Назад");

    QFile styleFile(":/styles/styles.css");
    styleFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString buttonStyle = QLatin1String(styleFile.readAll());
    styleFile.close();
    
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
    });
    connect(btnBlack, &QPushButton::clicked, [this]() { emit colorSelected(false); });
    connect(btnBack, &QPushButton::clicked, this, &ColorSelectionMenu::backRequested);
}