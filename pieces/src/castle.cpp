#include <iostream>
#include "..\\include\\castle.h"

castle::castle(const bool &Colour, const int &X, const int &Y): figure(Colour, X, Y){
}

castle::~castle(){
    std::cout << "Удалёна ладья" << std::endl;
}

bool castle::findObstacle(const int &X, const int &Y, const std::vector<std::vector<std::unique_ptr<figure>>>& board){
    int x = figure::getX();
    int y = figure::getY();
    if(x != X){
        while(x != (X > x ? X - 1 : X + 1) && (x >= 0 && x <= 7)){
            if(X > x){
                x++;
            }
            else{
                x--;
            }
            if(board[x][y] != nullptr){
                return 1;
            }
        }
    }
    if(y != Y){
        while(y != (Y > y ? Y - 1 : Y + 1) && (y >= 0 && y <= 7)){
            if(Y > y){
                y++;
            }
            else{
                y--;
            }
            if(board[x][y] != nullptr){
                return 1;
            }
        }
    }
    return 0;
}

bool castle::move(const int &X, const int &Y, const std::vector<std::vector<std::unique_ptr<figure>>>& board){
    if(((Y == figure::getY()) || (X == figure::getX())) &&
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

std::string castle::getImagePath() const {
    return isBlack() ? ":/img/castleB.png" : ":/img/castleW.png";
}

char castle::symbol() const { 
    return isBlack() ? '\u265C' : '\u2656'; 
}

bool castle::hasMoved() const {
    return moved;
}

void castle::setMoved(bool moved) {
    this->moved = moved;
}