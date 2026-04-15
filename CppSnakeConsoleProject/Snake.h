#pragma once
#include <vector>

enum class SnakeWay
{
	Left,
	Right,
	Up,
	Down
};

class Cell
{
	int row;
	int column;
public:
	Cell();
	Cell(int row, int column);

	int& Row();
	int& Column();

	friend bool operator==(Cell left, Cell right);
};

class Snake
{
	std::vector<Cell> snake;
	Cell head;

	int width;
	int height;

	int rowDiff;
	int columnDiff;
public:
	Snake(int width, int height);

	Cell& Head();

	Cell Move(SnakeWay way, bool grow = false);

	bool Fault();
};

