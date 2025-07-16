#include "..\\include\\StandbyMenu.h"
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include <iostream>

StandbyMenu::StandbyMenu(QWidget *parent) : QWidget(parent){
    numberOfPlayers = 1;

    this->setStyleSheet("position: relative;");

    numberMessage = new QLabel("Количество игроков 1/2");

    errorMessage = new QLabel();
    errorMessage->setObjectName("errorLabel");
    errorMessage->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    errorMessage->setAlignment(Qt::AlignCenter);
    errorMessage->setWordWrap(true);
    errorMessage->setVisible(false);

    startGame = new QPushButton("Начать игру"); 
    btnBack = new QPushButton("Назад");

    QFile styleFile(":/styles/styles.css");
    styleFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString styleSheet = QLatin1String(styleFile.readAll());
    styleFile.close();
    this->setStyleSheet(styleSheet);

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(numberMessage);
    layout->addWidget(errorMessage);
    layout->addWidget(startGame);
    layout->addWidget(btnBack);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(20);

    connect(startGame, &QPushButton::clicked, this, &StandbyMenu::IpCheckStart);
    connect(btnBack, &QPushButton::clicked, this, [this]() { emit backRequested(IsServer); });
}

void StandbyMenu::IpCheckStart(){
    if(numberOfPlayers == 1){
        errorMessage->setText("*Необходимо дождаться второго игрока");
        errorMessage->setVisible(true);
        errorMessage->setProperty("class", "visible");
    
        errorMessage->style()->unpolish(errorMessage);
        errorMessage->style()->polish(errorMessage);
        errorMessage->update();
    }
    else{
        qDebug() << "start game";
    }
}

void StandbyMenu::connection(bool isServer){
    if(!isServer){
        numberMessage->setText("Количество игроков 2/2");
        numberMessage->update();
        numberOfPlayers = 2;
    }
}