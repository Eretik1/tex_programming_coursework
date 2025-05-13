#pragma once
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class ColorSelectionMenu : public QWidget {
    Q_OBJECT  
public:
    explicit ColorSelectionMenu(QWidget *parent = nullptr);
    ~ColorSelectionMenu() override = default;

signals:
    void colorSelected(bool isWhite);  
    void backRequested();              

private:
    QPushButton *btnWhite;
    QPushButton *btnBlack;
    QPushButton *btnBack;
};