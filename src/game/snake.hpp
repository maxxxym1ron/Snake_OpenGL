#pragma once
#include "cell.hpp"
#include <vector>

struct Direction {
    inline static const Cell    up = { 0, 1 };
    inline static const Cell  down = { 0,-1 };
    inline static const Cell right = { 1, 0 };
    inline static const Cell  left = {-1, 0 };
};

class Snake {
private:
    Cell direction;

    std::vector<Cell> body;
    std::vector<Cell>::iterator headIt;
    Cell lastTail;

public:
    Snake(const int& weight, const int& height)
        : body( { { weight / 2, height / 2 }, { weight / 2 - 1, height / 2 } } ), 
        direction(Direction::right), headIt(body.begin()), lastTail(*body.rbegin()) {}

    const std::vector<Cell>& getBody() const { return body; }
    const Cell          getDirection() const { return direction; }
    const Cell            getHeadPos() const { return *headIt; }
    const Cell           getLastTail() const { return lastTail; }

    void setDirection(const Cell newDirection) { direction = newDirection; }

    const int getLength() { return body.size(); }

    void move();
    void increase();
};