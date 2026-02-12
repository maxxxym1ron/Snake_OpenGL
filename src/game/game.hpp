#pragma once
#include "apple.hpp"
#include "cell.hpp"
#include "field.hpp"
#include "snake.hpp"

enum class GameStatus {
    MENU,
    GAME,
    WIN,
    LOOSE
};

class Game {
    Field m_field;
    Snake m_snake;
    Apple m_apple;

    GameStatus m_status;

    bool m_wasAppleEaten;
    bool generateApple;

    bool checkLoose(const Cell& nextHeadPos, const Cell& fieldSize);

public:
    Game(const int& weight = 20, const int& height = 20, 
            const std::array<int, 3>& evenCellColor = { 30, 30, 30 }, 
            const std::array<int, 3>& oddCellColor = { 35, 35, 35 });
    
    const GameStatus status() const { return m_status; }

    const Apple& apple() const { return m_apple; }
    const Field& field() const { return m_field; }
    const Snake& snake() const { return m_snake; }

    Apple& apple() { return m_apple; }
    Snake& snake() { return m_snake; }

    void update();

    void reset();
};