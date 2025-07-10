#pragma once

#include <QWidget>
#include <QStackedWidget>
#include "MainMenu.h"
#include "ColorSelectionMenu.h"
#include "ChessWidget.h"
#include "IntermediateMenu.h"
#include "IpInputMenu.h"

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
    IntermediateMenu *intermediateMenu;
    IpInputMenu *ipInputMenu;
    chessboard* createNewGameBoard();
    std::unique_ptr<chessboard> gameBoard;

    void setupConnections();
    void initializeWidgets();
};