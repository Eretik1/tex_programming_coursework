#pragma once
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class MainMenu : public QWidget {
    Q_OBJECT  
public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu() override = default;

signals:
    void localGameRequested();  
    void onlineGameRequested();  

private:
    QPushButton *btnLocalGame;
    QPushButton *btnOnlineGame;
    QPushButton *btnQuit;
};