#pragma once

#include <QWidget>
#include <QStackedWidget>
#include "MainMenu.h"
#include "ColorSelectionMenu.h"
#include "ChessWidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private:
    QStackedWidget *stackedWidget;
    MainMenu *mainMenu;
    ColorSelectionMenu *colorMenu;
    ChessWidget *chessWidget;
    chessboard *gameBoard;
    chessboard* createNewGameBoard();

    void setupConnections();
    void initializeWidgets();
};