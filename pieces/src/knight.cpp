#include <iostream>
#include "..\\include\\knight.h"

knight::knight(const bool &Colour, const int &X, const int &Y): figure(Colour, X, Y){
}

knight::~knight(){
    std::cout << "Удалён конь" << std::endl;
}

bool knight::move(const int &X, const int &Y, const std::vector<std::vector<std::unique_ptr<figure>>>& board){
    if(((Y >= 0 && Y <= 7) && (X >= 0 && X <= 7)) &&
    ((abs(X - figure::getX()) == 1 && abs(Y - figure::getY()) == 2) || 
    (abs(X - figure::getX()) == 2 && abs(Y - figure::getY()) == 1))){
        if(board[X][Y] == nullptr){
            return 1;
        }
        else if(board[X][Y]->isBlack() != figure::isBlack()){
            return 1;
        }
    }
    return 0;
}

std::string knight::getImagePath() const {
    return isBlack() ? ":/img/knightB.png" : ":/img/knightW.png";
}

char knight::symbol() const { 
    return isBlack() ? '\u265E' : '\u2658'; 
}