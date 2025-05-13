#include <iostream>
#include "..\\include\\figure.h"

figure::figure(const bool &Colour, const int &X, const int &Y){
    colour = Colour;
    x = X;
    y = Y;
}

bool figure::isBlack() const{
    return colour;
}

void figure::setPosition(const int &x, const int &y){
    this->x = x;
    this->y = y;
}

int figure::getX(){
    return x;
}

int figure::getY(){
    return y;
}