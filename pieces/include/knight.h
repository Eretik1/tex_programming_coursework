#pragma once
#include "figure.h"

class knight : public figure{
    public:
    knight();
    knight(const bool &Colour, const int &X, const int &Y);
    ~knight();
    bool move(const int &X, const int &Y, const std::vector<std::vector<std::unique_ptr<figure>>>& board);
    std::string getImagePath() const override;
    char symbol() const override;
};