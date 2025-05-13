#pragma once
#include "figure.h"

class queen : public figure{
    public:
    queen();
    queen(const bool &Colour, const int &X, const int &Y);
    ~queen();
    bool move(const int &X, const int &Y, const std::vector<std::vector<std::unique_ptr<figure>>>& board);
    private:
    bool findObstacle(const int &X, const int &Y, const std::vector<std::vector<std::unique_ptr<figure>>>& board);
    std::string getImagePath() const override;
    char symbol() const override;
};