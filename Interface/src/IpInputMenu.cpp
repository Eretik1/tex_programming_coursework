#include "..\\include\\IpInputMenu.h"
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include <iostream>

IpInputMenu::IpInputMenu(QWidget *parent) : QWidget(parent){
    this->setStyleSheet("position: relative;");

    ipInputLine = new QLineEdit();

    errorMessage = new QLabel();
    errorMessage->setObjectName("errorLabel");
    errorMessage->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    errorMessage->setAlignment(Qt::AlignCenter);
    errorMessage->setWordWrap(true);
    errorMessage->setVisible(false);

    btnIpConfirmation = new QPushButton("Подключиться"); 
    btnBack = new QPushButton("Назад");

    QFile styleFile(":/styles/styles.css");
    styleFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString styleSheet = QLatin1String(styleFile.readAll());
    styleFile.close();
    this->setStyleSheet(styleSheet);

    btnIpConfirmation->setStyleSheet(styleSheet);

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(ipInputLine);
    layout->addWidget(errorMessage);
    layout->addWidget(btnIpConfirmation);
    layout->addWidget(btnBack);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(20);

    connect(btnIpConfirmation, &QPushButton::clicked, this, &IpInputMenu::IpCheck);
    connect(btnBack, &QPushButton::clicked, this, &IpInputMenu::backRequested);
}

void IpInputMenu::IpCheck(){
    if(ipInputLine->text().size() == 0){
        errorMessage->setText("*Необходимо ввести IP");
        errorMessage->setVisible(true);
        errorMessage->setProperty("class", "visible");
    
        errorMessage->style()->unpolish(errorMessage);
        errorMessage->style()->polish(errorMessage);
        errorMessage->update();
    }
    else{
        emit connection(ipInputLine->text());
        errorMessage->setText("*Не удалось подключиться по данному IP");
        errorMessage->setVisible(true);
        errorMessage->setProperty("class", "visible");
    
        errorMessage->style()->unpolish(errorMessage);
        errorMessage->style()->polish(errorMessage);
        errorMessage->update();
    }
}