#include <iostream>
#include "..\\include\\king.h"

king::king(const bool& Colour, const int& X, const int& Y) : figure(Colour, X, Y) {
}

king::~king() {
    std::cout << "Удалён король" << std::endl;
}

bool king::move(const int& X, const int& Y, const std::vector<std::vector<std::unique_ptr<figure>>>& board) {
    int currentX = getX();
    int currentY = getY();

    
    if (X >= 0 && X <= 7 && Y >= 0 && Y <= 7) {
        if ((abs(X - currentX) <= 1 && abs(Y - currentY) <= 1)) {
            if (board[X][Y] == nullptr || board[X][Y]->isBlack() != isBlack()) {
                return true;
            }
        }
        
        
        if (!moved && Y == currentY && abs(X - currentX) == 2) {
            return true; 
        }
    }
    return false;
}

std::string king::getImagePath() const {
    return isBlack() ? ":/img/kingB.png" : ":/img/kingW.png";
}



bool king::hasMoved() const {
    return moved;
}

void king::setMoved(bool moved) {
    this->moved = moved;
}

char king::symbol() const {
    return isBlack() ? '\u265A' : '\u2654';
}
