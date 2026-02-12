#pragma once
#include "cell.hpp"
#include <vector>

struct Direction {
    inline static const Cell    UP = { 0, 1 };
    inline static const Cell  DOWN = { 0,-1 };
    inline static const Cell RIGHT = { 1, 0 };
    inline static const Cell  LEFT = {-1, 0 };
};

class Snake {
private:
    Cell direction;
    bool m_haveNewDir;

    std::vector<Cell> body;
    std::vector<Cell>::iterator headIt;
    Cell lastTail;

public:
    Snake(const int& weight, const int& height)
        : body( { { weight / 2, height / 2 }, { weight / 2 - 1, height / 2 } } ), 
        direction(Direction::RIGHT), m_haveNewDir(false), headIt(body.begin()), lastTail(*body.rbegin()) {}

    void increase();
    void move();
    
    const std::vector<Cell>& getBody() const { return body; }
    const Cell          getDirection() const { return direction; }
    const Cell            getHeadPos() const { return *headIt; }
    const Cell           getLastTail() const { return lastTail; }
    const int              getLength() const { return body.size(); }
    const bool            haveNewDir() const { return m_haveNewDir; }

    void setDirection(const Cell newDirection) { direction = newDirection; m_haveNewDir = false; }
    void setHaveNewDir() { m_haveNewDir = true; }

    void reset(const int& weight, const int& height);
};