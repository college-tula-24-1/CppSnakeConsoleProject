#include "SnakeGame.h"

int SnakeGame::RandomRange(int low, int hi)
{
	return low + rand() % (hi - low + 1);
}

void SnakeGame::CellShow(int row, int column, Color color)
{
	std::string cellStr(cellSize * widthRate, ' ');
	
	Console::Background(color);

	for (int i{}; i < cellSize; i++)
		Console::WritePosition(
			{ rowStart + row, columnStart + column * widthRate },
			cellStr);
}

void SnakeGame::FieldShow()
{
	for (int row{}; row < height; row++)
	{
		CellShow(row, 0, wallFieldColor);
		CellShow(row, width, wallFieldColor);
	}

	for (int column{}; column < width; column++)
	{
		CellShow(0, column, wallFieldColor);
		CellShow(height, column, wallFieldColor);
	}
}

SnakeGame::SnakeGame(int rowStart, int columnStart, int width, int height)
	: rowStart{ rowStart },
	columnStart{ columnStart },
	width{ width },
	height{ height }
{
	snake = new Snake(width, height);
	food = new Cell(RandomRange(0, height), RandomRange(0, width));
}

void SnakeGame::Play()
{
	FieldShow();

	_getch();
}

SnakeGame::~SnakeGame()
{
	delete snake;
	delete food;
}
