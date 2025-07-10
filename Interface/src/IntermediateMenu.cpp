#include "..\\include\\IntermediateMenu.h"

IntermediateMenu::IntermediateMenu(QWidget *parent) : QWidget(parent){

    btnCreatingRoom = new QPushButton("Создать комнату");
    btnConnectionRoom = new QPushButton("Подключение по IP");
    btnBack = new QPushButton("Назад");

    QFile styleFile(":/styles/styles.css");
    styleFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString styleSheet = QLatin1String(styleFile.readAll());
    styleFile.close();
    

    btnCreatingRoom->setStyleSheet(styleSheet);
    btnConnectionRoom->setStyleSheet(styleSheet);
    btnBack->setStyleSheet(styleSheet);

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(btnCreatingRoom);
    layout->addWidget(btnConnectionRoom);
    layout->addWidget(btnBack);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(20);

    connect(btnCreatingRoom, &QPushButton::clicked, this, &IntermediateMenu::creatingRoomRequested);
    connect(btnConnectionRoom, &QPushButton::clicked, this, &IntermediateMenu::connectionRoomRequested);
    connect(btnBack, &QPushButton::clicked, this, &IntermediateMenu::backRequested);
}