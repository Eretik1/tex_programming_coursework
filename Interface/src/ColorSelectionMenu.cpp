#include "..\\include\\ColorSelectionMenu.h"

ColorSelectionMenu::ColorSelectionMenu(QWidget *parent) : QWidget(parent) {
    btnWhite = new QPushButton("Белые");
    btnBlack = new QPushButton("Чёрные");
    btnBack = new QPushButton("Назад");

    // Стилизация кнопок (аналогично главному меню)
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

    // Специальные стили для кнопок выбора цвета
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

    // Тёмный фон как в главном меню
    this->setStyleSheet("background-color: #2d2d2d;");

    // Оригинальные соединения
    connect(btnWhite, &QPushButton::clicked, [this]() { emit colorSelected(true); });
    connect(btnBlack, &QPushButton::clicked, [this]() { emit colorSelected(false); });
    connect(btnBack, &QPushButton::clicked, this, &ColorSelectionMenu::backRequested);
}