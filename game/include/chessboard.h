#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <functional>
#include "../../pieces/include/figure.h"
#include "../../pieces/include/pawn.h"
#include "../../pieces/include/castle.h"
#include "../../pieces/include/bishop.h"
#include "../../pieces/include/knight.h"
#include "../../pieces/include/queen.h"
#include "../../pieces/include/king.h"

class chessboard {
public:
    chessboard();
    virtual ~chessboard() = default;
    const std::vector<std::vector<std::unique_ptr<figure>>>& getBoard() const;
    void addFigure(int X, int Y, std::unique_ptr<figure> fig);
    void moveSquare(int x1, int y1, int x2, int y2);
    bool isBlackTurn() const;
    void switchTurn();
    void setupInitialPosition(); // Новый метод для начальной расстановки
    void setupFisherRandomRow(std::mt19937& gen, bool isWhite, int row);
    void setupMirroredRow(bool isWhite, int row);
    

private:
    std::vector<std::vector<std::unique_ptr<figure>>> board;
    bool blackTurn = false;
};