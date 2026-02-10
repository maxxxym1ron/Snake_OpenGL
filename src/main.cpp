#include <iostream>

#include "window.hpp"
#include "render/renderer.hpp"
#include "game/game.hpp"
#include "core/clock.hpp"

void drawField(Renderer& renderer, const Cell& fieldSize,
		const std::array<int, 3>& evenCellColor, const std::array<int, 3>& oddCellColor);
void drawSnake(Renderer& renderer, const std::vector<Cell>& bodySnake, const Cell& lastTail, const float& alpha);

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

	Cell appleLoc;
	Cell newSnakeDir = Direction::RIGHT;

	renderer.setFieldSize(fieldSize.x, fieldSize.y);

	Clock::startTime();

	while(!window.shouldClose()) {
		Clock::calculateTime();

		/* fps */
		if (Clock::fpsAccumulator >= 1.f) {
			window.setTitle(Clock::frames, game.snake().getLength());
			Clock::fpsAccumulator -= 1.f;
			Clock::frames = 0;
		}

		renderer.beginFrame(); // start render ==========
		drawField(renderer, fieldSize, oddCellColor, evenCellColor);

		/* draw apple */
		if (game.apple().isNew()) {
			appleLoc = game.apple().getPosition();
			game.apple().setOld();
		}
		renderer.drawApple(appleLoc.x, appleLoc.y, {150, 0, 0});

		drawSnake(renderer, game.snake().getBody(), game.snake().getLastTail(), Clock::alpha);
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
		if (game.status() == GameStatus::LOOSE) { window.close(); }
		if (game.status() == GameStatus::WIN) { window.close(); }

		window.swapBuffers();
		window.pollEvents();
	}

	return 0;
}

void drawField(Renderer& renderer, const Cell& fieldSize,
			const std::array<int, 3>& evenCellColor, const std::array<int, 3>& oddCellColor) {
	float fX;
	float fY;
	for (int y = 0; y < fieldSize.x; ++y) {
		for (int x = 0; x < fieldSize.y; ++x) {
			fX = static_cast<float>(x);
			fY = static_cast<float>(y);
			renderer.drawCell({ fX, fY },
				(x + y) % 2 == 0 ? oddCellColor : evenCellColor
			);
		}
	}
}

void drawSnake(Renderer& renderer, const std::vector<Cell>& bodySnake, const Cell& lastTail, const float& alpha) {
	float cellX, cellY;
	int colMix = 0;

	auto it = bodySnake.begin() + 1;
	for (it; it + 1 != bodySnake.end(); ++it) {
		cellX = static_cast<float>((*it).x);
		cellY = static_cast<float>((*it).y);
		renderer.drawCell({cellX, cellY}, {0, 100 + colMix, 0});
		++colMix;
	}

	/* static pre tail */
	cellX = static_cast<float>((*it).x);
	cellY = static_cast<float>((*it).y);
	renderer.drawCell({cellX, cellY}, {0, 100 + colMix, 0});

	/* dynamic tail */
	cellX = static_cast<float>(lastTail.x) + static_cast<float>((*it - lastTail).x) * alpha;
	cellY = static_cast<float>(lastTail.y) + static_cast<float>((*it - lastTail).y) * alpha;
	renderer.drawCell({cellX, cellY}, {0, 100 + colMix, 0});

	/* dynamic head */
	it = bodySnake.begin();
	Cell prev = *(it + 1);
	
	cellX = static_cast<float>(prev.x) + static_cast<float>((*it - prev).x) * alpha;
	cellY = static_cast<float>(prev.y) + static_cast<float>((*it - prev).y) * alpha;
	renderer.drawCell({cellX, cellY}, {0, 100, 0});
}

void CheckPressedKeys(const Window &window, Game &game,
                      Cell &newSnakeDir)
{
    if (window.isKeyPressed(GLFW_KEY_ESCAPE)) {
		window.close();
	}	
	else if (window.isKeyPressed(GLFW_KEY_W) || window.isKeyPressed(GLFW_KEY_A) ||
			 window.isKeyPressed(GLFW_KEY_S) || window.isKeyPressed(GLFW_KEY_D) ||
			 window.isKeyPressed(GLFW_KEY_UP) || window.isKeyPressed(GLFW_KEY_LEFT) ||
			 window.isKeyPressed(GLFW_KEY_DOWN) || window.isKeyPressed(GLFW_KEY_RIGHT)) {
		Cell snakeDirection = game.snake().getDirection();

		if ((window.isKeyPressed(GLFW_KEY_W) || window.isKeyPressed(GLFW_KEY_UP)) && 
				snakeDirection != Direction::UP && 
				snakeDirection != Direction::DOWN) {
			newSnakeDir = Direction::UP;
			game.snake().setHaveNewDir();
		}

		if ((window.isKeyPressed(GLFW_KEY_A) || window.isKeyPressed(GLFW_KEY_LEFT)) && 
				snakeDirection != Direction::LEFT && 
				snakeDirection != Direction::RIGHT) {
			newSnakeDir = Direction::LEFT;
			game.snake().setHaveNewDir();
		}

		if ((window.isKeyPressed(GLFW_KEY_S) || window.isKeyPressed(GLFW_KEY_DOWN)) && 
				snakeDirection != Direction::UP && 
				snakeDirection != Direction::DOWN) {
			newSnakeDir = Direction::DOWN;
			game.snake().setHaveNewDir();
		}

		if ((window.isKeyPressed(GLFW_KEY_D) || window.isKeyPressed(GLFW_KEY_RIGHT)) && 
				snakeDirection != Direction::LEFT && 
				snakeDirection != Direction::RIGHT) {
			newSnakeDir = Direction::RIGHT;
			game.snake().setHaveNewDir();
		}
	}
}