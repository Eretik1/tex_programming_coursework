#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <functional>
#include <string>
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
    bool moveSquare(int x1, int y1, int x2, int y2);
    bool isBlackTurn() const;
    void switchTurn();
    void setupInitialPosition();
    void setupFisherRandomRow(std::mt19937& gen, bool isWhite, int row);
    void setupMirroredRow(bool isWhite, int row);
    bool isCheck(bool forBlack) const;
    bool isCheckmate(bool forBlack);
    bool isStalemate(bool forBlack);
    bool isValidPosition(int x, int y) const;
    bool isKingInCheck(bool isBlack) const;
    std::pair<int, int> findKing(bool isBlack) const;
    bool isGameOver() const;
    std::string getGameResult() const;


private:
    std::vector<std::vector<std::unique_ptr<figure>>> board;
    bool canCastle(int x1, int y1, int x2, int y2) const;
    bool isSquareUnderAttack(int x, int y, bool byBlack) const;
    bool hasLegalMoves(bool forBlack);
    bool blackTurn = false;
    std::pair<int, int> enPassantTarget = {-1, -1}; // Поле для взятия на проходе
    bool gameOver = false;
    std::string gameResult;
};