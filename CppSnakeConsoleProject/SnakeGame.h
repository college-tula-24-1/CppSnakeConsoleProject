#pragma once
#include <ctime>

#include "View.h"
class SnakeGame
{
	Position position;
	Size size;

	std::vector<View*> snake;
	View* snakeHead;

	View* food;

	const int widthRate{ 2 };
	const int cellSize{ 2 };
	const Color colorWall{ Color::Magenta };
	const Color colorHead{ Color::Green };
	const Color colorSnake{ Color::Yellow };
	const Color colorFood{ Color::Red };

	void FieldShow();
	void SnakeShow(bool visible = true);
	int RandRange(int low, int hi);
	void FoodShow();

public:
	SnakeGame(Position position, Size size = { 40, 30 });

	void Play();
};

