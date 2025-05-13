#pragma once
#include "figure.h"

class king : public figure {
public:
    king();
    king(const bool& Colour, const int& X, const int& Y);
    ~king();
    bool move(const int& X, const int& Y, const std::vector<std::vector<std::unique_ptr<figure>>>& board) override;
    std::string getImagePath() const override;
    char symbol() const override;
    bool hasMoved() const;
    void setMoved(bool moved);

private:
    bool moved = false;
};