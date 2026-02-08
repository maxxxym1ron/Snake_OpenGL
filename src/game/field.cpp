#include "field.hpp"

void Field::addFreeCell(const Cell& cell) { m_freeCells.push_back(cell); }

void Field::removeFreeCell(const Cell& cell) {
    for (auto it = m_freeCells.begin(); it != m_freeCells.end(); ++it) {
        if (*it == cell) {
            *it = m_freeCells.back();
            m_freeCells.pop_back();
            return;
        }
    }
}