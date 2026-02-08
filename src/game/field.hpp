#pragma once
#include "cell.hpp"

#include <array>
#include <vector>

class Field {
    int m_weight;
    int m_height;

    std::array<int, 3> m_evenCellColor;
    std::array<int, 3> m_oddCellColor;

    std::vector<Cell> m_freeCells;

public:
    Field(const int& weight, const int& height, const std::array<int, 3> evenCellColor, const std::array<int, 3> oddCellColor) 
        : m_weight(weight), m_height(height), m_evenCellColor(evenCellColor), m_oddCellColor(oddCellColor),
          m_freeCells(weight * height, { 0, 0 }) {
        
        unsigned short count = 0;
        for (int y = 0; y < m_weight; ++y) {
            for (int x = 0; x < m_height; ++x) {
                m_freeCells[count] = {x, y};
                ++count;
            }
        }
    }

    const Cell              getFieldSize() const { return {m_weight, m_height}; }
    const std::vector<Cell> getFreeCells() const { return m_freeCells; }

    const std::array<int, 3>& getEvenCellColor() const { return m_evenCellColor; }
    const std::array<int, 3>&  getOddCellColor() const { return m_oddCellColor; }

    void addFreeCell(const Cell& cell);
    void removeFreeCell(const Cell& cell);
    const int getFreeCellsSize() const { return m_freeCells.size(); }
};