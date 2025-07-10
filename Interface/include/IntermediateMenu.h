#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QStyle>

class IntermediateMenu : public QWidget {
    Q_OBJECT

public:
    IntermediateMenu(QWidget *parent = nullptr);
    ~IntermediateMenu() override = default;

signals:
    void creatingRoomRequested();  
    void connectionRoomRequested();  
    void backRequested();    

private:
    QPushButton *btnCreatingRoom;
    QPushButton *btnConnectionRoom;
    QPushButton *btnBack;
};