#pragma once
#include <vector>
#include <memory>
#include <string>

class figure{
    public:
    figure();
    figure(const bool &Colour, const int &X, const int &Y);
    virtual ~figure() = default;
    virtual bool move(const int &X, const int &Y, const std::vector<std::vector<std::unique_ptr<figure>>>& board) = 0;
    bool isBlack() const;
    void setPosition(const int &x, const int &y);
    int getX();
    int getY();
    virtual std::string getImagePath() const = 0;
    virtual char symbol() const = 0;

    private:
    std::string pathW;
    std::string pathB;
    bool colour;
    int x;
    int y;
};

