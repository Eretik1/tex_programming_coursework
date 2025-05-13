#pragma once
#include "figure.h"

class castle : public figure{
    public:
    castle();
    castle(const bool &Colour, const int &X, const int &Y);
    ~castle();
    bool move(const int &X, const int &Y, const std::vector<std::vector<std::unique_ptr<figure>>>& board);
    bool hasMoved() const;
    void setMoved(bool moved);
    private:
    bool findObstacle(const int &X, const int &Y, const std::vector<std::vector<std::unique_ptr<figure>>>& board);
    std::string getImagePath() const override;
    char symbol() const override;

    private:
    bool moved = false;
};