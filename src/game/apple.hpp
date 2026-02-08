#pragma once
#include "cell.hpp"
#include <vector>

class Apple {
    Cell m_position;

public:
    // TODO: add parameter like snakeLength
    Apple(const Cell& nullPos): m_position(nullPos) {};

    void generateApple(const std::vector<Cell>& freeCells);

    const Cell& getPosition() const { return m_position; }
};