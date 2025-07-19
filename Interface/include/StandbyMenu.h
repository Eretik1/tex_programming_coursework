#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QFile>
#include <QStyle>

class StandbyMenu : public QWidget {
    Q_OBJECT

public:
    StandbyMenu(QWidget *parent = nullptr);
    ~StandbyMenu() override = default;
    bool IsServer;

signals:
    void backRequested(bool isServer); 
    void start(); 
    
public slots:
    void connection(bool isServer);
    void disconnection();

private:
    QLabel *numberMessage;
    QLabel *errorMessage;
    QPushButton *startGame;
    QPushButton *btnBack;
    int numberOfPlayers;

    void IpCheckStart();
};