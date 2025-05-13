#include "..\\include\\MainMenu.h"
#include <QApplication>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent) {
    btnLocalGame = new QPushButton("Локальная игра");
    btnOnlineGame = new QPushButton("Сетевая игра");
    btnQuit = new QPushButton("Выход");

    // Стилизация кнопок (новый дизайн)
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

    btnLocalGame->setStyleSheet(buttonStyle);
    btnOnlineGame->setStyleSheet(buttonStyle);
    btnQuit->setStyleSheet(buttonStyle);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(btnLocalGame);
    layout->addWidget(btnOnlineGame);
    layout->addWidget(btnQuit);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(20);

    // Установка тёмного фона (новый дизайн)
    this->setStyleSheet("background-color: #2d2d2d;");

    // Оригинальные соединения
    connect(btnLocalGame, &QPushButton::clicked, this, &MainMenu::localGameRequested);
    connect(btnOnlineGame, &QPushButton::clicked, this, &MainMenu::onlineGameRequested);
    connect(btnQuit, &QPushButton::clicked, qApp, &QApplication::quit);
}