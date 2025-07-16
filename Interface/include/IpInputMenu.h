#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QFile>
#include <QStyle>
#include "..\\..\\network_game\\include\\GameClient.h"

class IpInputMenu : public QWidget {
    Q_OBJECT

public:
    IpInputMenu(QWidget *parent = nullptr);
    ~IpInputMenu() override = default;

signals:
    void backRequested();    
    void connection(QString IP); 

private:
    QLineEdit *ipInputLine;
    QLabel *errorMessage;
    QPushButton *btnIpConfirmation;
    QPushButton *btnBack;
    Client *client;

    void IpCheck();
};