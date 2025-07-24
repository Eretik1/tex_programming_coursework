#include "..\\include\\ResultsMenu.h"
#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include <iostream>

ResultsMenu::ResultsMenu(QWidget *parent) : QWidget(parent){
    this->setStyleSheet("position: relative;");

    ResultsMassege = new QLabel();
    ResultsMassege->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    ResultsMassege->setAlignment(Qt::AlignCenter);
    ResultsMassege->setWordWrap(true);

    btnBack = new QPushButton("Продолжить");

    QFile styleFile(":/styles/styles.css");
    styleFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString styleSheet = QLatin1String(styleFile.readAll());
    styleFile.close();
    this->setStyleSheet(styleSheet);

    
    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(ResultsMassege);
    layout->addWidget(btnBack);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(20);

    connect(btnBack, &QPushButton::clicked, this, &ResultsMenu::backRequested);
}

void ResultsMenu::setResults(const QString &Results){
    if(Results == "WHITES_SURRENDERED"){
        ResultsMassege->setText("Белые сдались");
    }
    else if(Results == "BLACK_SURRENDERED"){
        ResultsMassege->setText("Черные сдались");
    }
    ResultsMassege->update();
}