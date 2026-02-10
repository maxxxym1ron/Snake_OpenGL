#include <iostream>

#include "window.hpp"
#include "render/renderer.hpp"
#include "game/game.hpp"
#include "core/clock.hpp"

void drawField(Renderer& renderer, const Cell& fieldSize,
		const std::array<int, 3>& evenCellColor, const std::array<int, 3>& oddCellColor);
void drawSnake(Renderer& renderer, const std::vector<Cell>& snakeBody);

void CheckPressedKeys(const Window& window, Game& game, Cell& newSnakeDir);

int main() {
	/* Create main objects */
	Window window(800, 800, false);
	Renderer renderer;
	if(!renderer.getSuccessInfo()) {
		window.terminate();
		return -1;
	}
	Game game;
	/* End Create */

	const Cell fieldSize = game.field().getFieldSize();
	const std::array<int, 3> evenCellColor = game.field().getEvenCellColor();
	const std::array<int, 3> oddCellColor = game.field().getOddCellColor();

	Cell appleLocation;
	Cell newSnakeDir = Direction::RIGHT;

	renderer.setFieldSize(fieldSize.x, fieldSize.y);

	Clock::startTime();

	while(!window.shouldClose()) {
		Clock::calculateTime();

		/* fps */
		if (Clock::fpsAccumulator >= 1.f) {
			window.setTitle(Clock::frames);
			Clock::fpsAccumulator -= 1.f;
			Clock::frames = 0;
		}

		renderer.beginFrame(); // start render ==========
		drawField(renderer, fieldSize, oddCellColor, evenCellColor);

		/* draw apple */
		if (game.apple().isNew()) {
			appleLocation = game.apple().getPosition();
			game.apple().setOld();
		}
		renderer.drawCell({ appleLocation.x , appleLocation.y }, { 150, 0, 0 });

		drawSnake(renderer, game.snake().getBody());
		renderer.endFrame(); // end render =============

		CheckPressedKeys(window, game, newSnakeDir);
		
		if (game.status() == GameStatus::GAME) { 
			while(Clock::gameUpdateAccumulator >= Clock::stepTime) {
				if (game.snake().haveNewDir())
					game.snake().setDirection(newSnakeDir);	
				game.update();
			
				Clock::gameUpdateAccumulator -= Clock::stepTime;
			}
		}
		else if (game.status() == GameStatus::LOOSE) { window.close(); }
		else if (game.status() == GameStatus::WIN) { window.close(); }

		window.swapBuffers();
		window.pollEvents();
	}

	return 0;
}

void drawField(Renderer& renderer, const Cell& fieldSize,
			const std::array<int, 3>& evenCellColor, const std::array<int, 3>& oddCellColor) {
	for (int y = 0; y < fieldSize.x; ++y) {
		for (int x = 0; x < fieldSize.y; ++x) {
			renderer.drawCell({ x , y },
				(x + y) % 2 == 0 ? oddCellColor : evenCellColor
			);
		}
	}
}

void drawSnake(Renderer& renderer, const std::vector<Cell>& bodySnake) {
	for (const Cell& e : bodySnake)
		renderer.drawCell({ e.x, e.y }, { 0, 100, 0 });
}

void CheckPressedKeys(const Window &window, Game &game,
                      Cell &newSnakeDir)
{
    if (window.isKeyPressed(GLFW_KEY_ESCAPE)) {
		window.close();
	}	
	else if (window.isKeyPressed(GLFW_KEY_W) || window.isKeyPressed(GLFW_KEY_A) ||
		window.isKeyPressed(GLFW_KEY_S) || window.isKeyPressed(GLFW_KEY_D)) {
		Cell snakeDirection = game.snake().getDirection();

		if (window.isKeyPressed(GLFW_KEY_W) && 
				snakeDirection != Direction::UP && 
				snakeDirection != Direction::DOWN) {
			newSnakeDir = Direction::UP;
			game.snake().setHaveNewDir();
		}

		if (window.isKeyPressed(GLFW_KEY_A) && 
				snakeDirection != Direction::LEFT && 
				snakeDirection != Direction::RIGHT) {
			newSnakeDir = Direction::LEFT;
			game.snake().setHaveNewDir();
		}

		if (window.isKeyPressed(GLFW_KEY_S) && 
				snakeDirection != Direction::UP && 
				snakeDirection != Direction::DOWN) {
			newSnakeDir = Direction::DOWN;
			game.snake().setHaveNewDir();
		}

		if (window.isKeyPressed(GLFW_KEY_D) && 
				snakeDirection != Direction::LEFT && 
				snakeDirection != Direction::RIGHT) {
			newSnakeDir = Direction::RIGHT;
			game.snake().setHaveNewDir();
		}
	}
}