#include <iostream>
#include "..\\include\\pawn.h"

pawn::pawn(const bool &Colour, const int &X, const int &Y): figure(Colour, X, Y){
}

pawn::~pawn(){
    std::cout << "Удалёна пешка" << std::endl;
}

bool pawn::move(const int &X, const int &Y, const std::vector<std::vector<std::unique_ptr<figure>>>& board){
    if(((figure::isBlack() && Y == figure::getY() - 1) || (figure::isBlack() == 0 && Y == figure::getY() + 1)) &&
        (Y >= 0 && Y <= 7))
    {
        if(X == figure::getX() && board[X][Y] == nullptr){
            return 1;
        }
        if((X >= 0 && X <= 7) && (X == figure::getX() + 1 || X == figure::getX() - 1) && 
        board[X][Y] != nullptr && 
        board[X][Y]->isBlack() != figure::isBlack())
        {
            return 1; 
        }
    }
    if(figure::isBlack() && Y == 4 && figure::getY() == 6){
        return 1;
    }
    if(!figure::isBlack() && Y == 3 && figure::getY() == 1){
        return 1;
    }
    return 0;
}

std::string pawn::getImagePath() const {
    return isBlack() ? ":/img/pawnB.png" : ":/img/pawnW.png";
}

char pawn::symbol() const { 
    return isBlack() ? '\u265F' : '\u2659'; 
}