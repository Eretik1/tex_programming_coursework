#include <iostream>
#include "..\\include\\queen.h"

queen::queen(const bool &Colour, const int &X, const int &Y): figure(Colour, X, Y){
}

queen::~queen(){
    std::cout << "Удалёна королева" << std::endl;
}

bool queen::findObstacle(const int &X, const int &Y, const std::vector<std::vector<std::unique_ptr<figure>>>& board){
    int x = figure::getX();
    int y = figure::getY();
    if((Y == figure::getY()) || (X == figure::getX())){
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
    }
    else{
        while(x != (X > x ? X - 1 : X + 1) && y != (Y > y ? Y - 1 : Y + 1) &&
        (x >= 0 && x <= 7) && (y >= 0 && y <= 7)){
            x += X > x ? 1 : -1;
            y += Y > y ? 1 : -1;
            if(board[x][y] != nullptr){
                return 1;
            }
        }
    }
    return 0;
}

bool queen::move(const int &X, const int &Y, const std::vector<std::vector<std::unique_ptr<figure>>>& board){
    if(((Y >= 0 && Y <= 7) && (X >= 0 && X <= 7)) &&
    (((Y == figure::getY()) || (X == figure::getX())) ||
    (abs(X - figure::getX()) == abs(Y - figure::getY()))) &&
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

std::string queen::getImagePath() const {
    return isBlack() ? ":/img/queenB.png" : ":/img/queenW.png";
}

char queen::symbol() const { 
    return isBlack() ? '\u265B' : '\u2655'; 
}