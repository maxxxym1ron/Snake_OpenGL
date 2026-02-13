#include "snake.hpp"

void Snake::increase() {
    m_body.push_back(m_lastTail);
    m_headIt = m_body.begin();
}

void Snake::move() {
    auto it = m_body.rbegin();
    m_lastTail = *it;
    for (it; it + 1 != m_body.rend(); ++it) {
        *it = *(it + 1);
    }
    *m_headIt += m_direction;
}

void Snake::reset(const int& weight, const int& height) {
    m_body.clear();
    m_body = std::vector<Cell>{{ weight / 2, height / 2 }, { weight / 2 - 1, height / 2 }};

    m_direction = Direction::RIGHT;
    m_haveNewDir = false;

    m_headIt = m_body.begin();
    m_lastTail = *m_body.rbegin();
}