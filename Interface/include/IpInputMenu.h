#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QFile>
#include <QStyle>

class IpInputMenu : public QWidget {
    Q_OBJECT

public:
    IpInputMenu(QWidget *parent = nullptr);
    ~IpInputMenu() override = default;

signals:
    void backRequested();    

private:
    QLineEdit *ipInputLine;
    QLabel *errorMessage;
    QPushButton *btnIpConfirmation;
    QPushButton *btnBack;

    void IpCheck();
};