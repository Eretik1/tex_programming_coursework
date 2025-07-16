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

signals:
    void backRequested(bool isServer); 
    
public slots:
    void connection(bool isServer);

private:
    QLabel *numberMessage;
    QLabel *errorMessage;
    QPushButton *startGame;
    QPushButton *btnBack;
    int numberOfPlayers;
    bool IsServer;

    void IpCheckStart();
};