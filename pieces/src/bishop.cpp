#include <iostream>
#include "..\\include\\bishop.h"

bishop::bishop(const bool &Colour, const int &X, const int &Y): figure(Colour, X, Y){
}

bishop::~bishop(){
    std::cout << "Удалён слон" << std::endl;
}

bool bishop::findObstacle(const int &X, const int &Y, const std::vector<std::vector<std::unique_ptr<figure>>>& board){
    int x = figure::getX();
    int y = figure::getY();
    while(x != (X > x ? X - 1 : X + 1) && y != (Y > y ? Y - 1 : Y + 1) &&
        (x >= 0 && x <= 7) && (y >= 0 && y <= 7))
    {
        x += X > x ? 1 : -1;
        y += Y > y ? 1 : -1;
        if(board[x][y] != nullptr){
            return 1;
        }
    }
    return 0;
}

bool bishop::move(const int &X, const int &Y, const std::vector<std::vector<std::unique_ptr<figure>>>& board){
    if(abs(X - figure::getX()) == abs(Y - figure::getY()) &&
    ((Y >= 0 && Y <= 7) && (X >= 0 && X <= 7)) &&
    !findObstacle(X, Y, board)){
        if(board[X][Y] == nullptr){
            return 1;
        }
        else if(board[X][Y]->isBlack() != figure::isBlack()){
            return 1;
        }
    }
    return 0;
}

std::string bishop::getImagePath() const {
    return isBlack() ? ":/img/bishopB.png" : ":/img/bishopW.png";
}

char bishop::symbol() const { 
    return isBlack() ? '\u265D' : '\u2657'; 
}