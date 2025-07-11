#include "..\\include\\MainMenu.h"
#include <QApplication>
#include <QFile>
#include <QStyle>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent) {
    btnLocalGame = new QPushButton("Локальная игра");
    btnOnlineGame = new QPushButton("Сетевая игра");
    btnQuit = new QPushButton("Выход");

    QFile styleFile(":/styles/styles.css");
    styleFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString buttonStyle = QLatin1String(styleFile.readAll());
    styleFile.close();

    btnLocalGame->setStyleSheet(buttonStyle);
    btnOnlineGame->setStyleSheet(buttonStyle);
    btnQuit->setStyleSheet(buttonStyle);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(btnLocalGame);
    layout->addWidget(btnOnlineGame);
    layout->addWidget(btnQuit);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(20);

    
    this->setStyleSheet("background-color: #2d2d2d;");

    
    connect(btnLocalGame, &QPushButton::clicked, this, &MainMenu::localGameRequested);
    connect(btnOnlineGame, &QPushButton::clicked, this, &MainMenu::onlineGameRequested);
    connect(btnQuit, &QPushButton::clicked, qApp, &QApplication::quit);
}