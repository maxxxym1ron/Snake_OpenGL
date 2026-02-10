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