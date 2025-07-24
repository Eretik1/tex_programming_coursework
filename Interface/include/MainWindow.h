#pragma once

#include <QWidget>
#include <QStackedWidget>
#include "MainMenu.h"
#include "ColorSelectionMenu.h"
#include "ChessWidget.h"
#include "IntermediateMenu.h"
#include "IpInputMenu.h"
#include "StandbyMenu.h"
#include "ResultsMenu.h"
#include "..\\..\\network_game\\include\\GameServer.h"
#include "..\\..\\network_game\\include\\GameClient.h"

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
    StandbyMenu *standbyMenu;
    ResultsMenu *resultsMenu;
    Server *server = nullptr;
    Client *client = nullptr;
    chessboard* createNewGameBoard();
    std::unique_ptr<chessboard> gameBoard;
    bool IsWhite;

    void setupConnections();
    void initializeWidgets();
};