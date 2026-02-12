#include "snake.hpp"

void Snake::increase() {
    body.push_back(lastTail);
    headIt = body.begin();
}

void Snake::move() {
    auto it = body.rbegin();
    lastTail = *it;
    for (it; it + 1 != body.rend(); ++it) {
        *it = *(it + 1);
    }

    *headIt += direction;
}

void Snake::reset(const int& weight, const int& height) {
    body.clear();
    body = std::vector<Cell>{{ weight / 2, height / 2 }, { weight / 2 - 1, height / 2 }};

    direction = Direction::RIGHT;
    m_haveNewDir = false;

    headIt = body.begin();
    lastTail = *body.rbegin();
}