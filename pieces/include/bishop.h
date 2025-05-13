#pragma once
#include "figure.h"

class bishop : public figure{
    public:
    bishop();
    bishop(const bool &Colour, const int &X, const int &Y);
    ~bishop();
    bool move(const int &X, const int &Y, const std::vector<std::vector<std::unique_ptr<figure>>>& board);
    private:
    bool findObstacle(const int &X, const int &Y, const std::vector<std::vector<std::unique_ptr<figure>>>& board);
    std::string getImagePath() const override;
    char symbol() const override;
};