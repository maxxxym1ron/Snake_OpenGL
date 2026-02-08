#include <iostream>

#include "window.hpp"
#include "render/renderer.hpp"
#include "game/game.hpp"
#include "core/clock.hpp"

void CheckPressedKeys(const Window& window, const Game& game, Cell& newDirectionForSnake, bool& getNewDirectionForSnake);

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

	bool getNewDirectionForSnake = false;
	Cell newDirectionForSnake = {1, 0};

	Clock::startTime();

	while(!window.shouldClose()) {
		Clock::calculateTime();

		/* fps */
		if (Clock::accumulator2 >= 1.f) {
			window.setTitle(Clock::frames);
			Clock::accumulator2 -= 1.f;
			Clock::frames = 0;
		}

		renderer.beginFrame();

		/* Draw field */
		for (int y = 0; y < fieldSize.x; ++y) {
			for (int x = 0; x < fieldSize.y; ++x) {
				renderer.drawCell(fieldSize.x, fieldSize.y, { x , y },
					(x + y) % 2 == 0 ? oddCellColor : evenCellColor
				);
			}
		}

		/* draw apple */
		if (game.getInfoApple()) {
			appleLocation = game.apple().getPosition();
			game.appleIsOld();
		}
		renderer.drawCell(fieldSize.x, fieldSize.y, { appleLocation.x , appleLocation.y },
			{ 150, 0, 0 });

		/* draw snake */
		const std::vector<Cell> bodySnake = game.snake().getBody();
		for (const Cell& e : bodySnake) {
			renderer.drawCell(fieldSize.x, fieldSize.y, { e.x, e.y }, { 0, 150, 0 });
		}

		renderer.endFrame();

		CheckPressedKeys(window, game, newDirectionForSnake, getNewDirectionForSnake);
		
		if (game.status() == GameStatus::GAME) { 
			while(Clock::accumulator1 >= Clock::stepTime) {
				if (getNewDirectionForSnake) {
					game.snake().setDirection(newDirectionForSnake);
				}
				game.step();
				Clock::accumulator1 -= Clock::stepTime;
				getNewDirectionForSnake = false;
			}
		}
		else if (game.status() == GameStatus::LOOSE) { std::cout << "LOOSE" << std::endl; window.close(); }
		else if (game.status() == GameStatus::WIN) { std::cout << "WIN" << std::endl; window.close(); }

		window.swapBuffers();
		window.pollEvents();
	}

	return 0;
}

void CheckPressedKeys(const Window& window, const Game& game, 
		Cell& newDirectionForSnake, bool& getNewDirectionForSnake) {
	if (window.isKeyPressed(GLFW_KEY_W) || window.isKeyPressed(GLFW_KEY_A) ||
		window.isKeyPressed(GLFW_KEY_S) || window.isKeyPressed(GLFW_KEY_D)) {
		Cell snakeDirection = game.snake().getDirection();

		if (window.isKeyPressed(GLFW_KEY_W) && 
			snakeDirection != Direction::up && 
			snakeDirection != Direction::down) {
			newDirectionForSnake = Direction::up;
		}

		if (window.isKeyPressed(GLFW_KEY_A) && 
			snakeDirection != Direction::left && 
			snakeDirection != Direction::right) {
			newDirectionForSnake = Direction::left;
		}

		if (window.isKeyPressed(GLFW_KEY_S) && 
			snakeDirection != Direction::up && 
			snakeDirection != Direction::down) {
			newDirectionForSnake = Direction::down;
		}

		if (window.isKeyPressed(GLFW_KEY_D) && 
			snakeDirection != Direction::left && 
			snakeDirection != Direction::right) {
			newDirectionForSnake = Direction::right;
		}
		getNewDirectionForSnake = true;
	}
}