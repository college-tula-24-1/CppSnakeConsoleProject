#pragma once
#include <conio.h>

#include "Console.h"
#include "Snake.h"

class SnakeGame
{
	int rowStart;
	int columnStart;

	int width;
	int height;

	Cell* food;
	Snake* snake;

	const Color backFieldColor{ Color::Black };
	const Color wallFieldColor{ Color::Magenta };
	const Color snakeHeadColor{ Color::Green };
	const Color snakeBodyColor{ Color::Blue };
	const Color foodColor{ Color::Red };

	const int cellSize{ 2 };
	const int widthRate{ 2 };

	int RandomRange(int low, int hi);
	void CellShow(int row, int column, Color color);
	void FieldShow();
public:
	SnakeGame(int rowStart, int columnStart, int width, int height);

	void Play();

	~SnakeGame();
};

