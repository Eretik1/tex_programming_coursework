#pragma once
#include "figure.h"

class pawn : public figure{
    public:
    pawn();
    pawn(const bool &Colour, const int &X, const int &Y);
    ~pawn();
    bool move(const int &X, const int &Y, const std::vector<std::vector<std::unique_ptr<figure>>>& board);
    std::string getImagePath() const override;
    char symbol() const override;
};