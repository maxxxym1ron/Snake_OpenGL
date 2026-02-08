#include "game.hpp"

Game::Game(const int& weight, const int& height, 
           const std::array<int, 3>& evenCellColor, 
           const std::array<int, 3>& oddCellColor)
            : m_field(weight, height, evenCellColor, oddCellColor), 
              m_snake(weight, height), m_status(GameStatus::GAME),
              m_apple({-1, -1}), newApple(true) {
    for (const Cell& bodyCell : m_snake.getBody()) {
        m_field.removeFreeCell(bodyCell);
    }
    m_apple.generateApple(m_field.getFreeCells());
    m_field.removeFreeCell(m_apple.getPosition());
}

bool Game::checkLoose(const Cell& nextHeadPos, const Cell& fieldSize) {
    if (nextHeadPos.x == fieldSize.x || nextHeadPos.x == -1 || 
        nextHeadPos.y == fieldSize.y || nextHeadPos.y == -1) {
        m_status = GameStatus::LOOSE;
        return false;
    }
    
    std::vector<Cell> snakeBody = m_snake.getBody();
    for (auto it = snakeBody.rbegin(); it + 2 != snakeBody.rend(); ++it) {
        if (nextHeadPos == *it) {
            m_status = GameStatus::LOOSE;
            return false;
        }
    }

    return true;
}

void Game::step() {
    const Cell headPos = m_snake.getHeadPos();
    const Cell snakeDirection = m_snake.getDirection();
    const Cell fieldSize = m_field.getFieldSize();

    const Cell newHeadPos = headPos + snakeDirection;

    if (checkLoose(newHeadPos, fieldSize)) {
        m_snake.move();
        
        if (newHeadPos == m_apple.getPosition()) {
            m_snake.increase();
            if (m_snake.getLength() == fieldSize.x * fieldSize.y) {
                m_status = GameStatus::WIN;
                return;
            }
            m_apple.generateApple(m_field.getFreeCells());
            m_field.removeFreeCell(m_apple.getPosition());
            newApple = true;
        }
        else {
            m_field.addFreeCell(m_snake.getLastTail());
            m_field.removeFreeCell(newHeadPos);
        }
    }
    // TODO: else { deathAnimation }
}