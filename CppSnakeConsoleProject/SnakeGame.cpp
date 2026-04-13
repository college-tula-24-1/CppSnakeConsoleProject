#include "SnakeGame.h"

void SnakeGame::FieldShow()
{
	View* view;

	for (int column{ position.column }; column <= position.column + size.width; column++)
	{
		view = new View({ position.row, column * widthRate },
			{ cellSize * widthRate, cellSize },
			colorWall);
		view->Show();

		view = new View({ position.row + size.height, column * widthRate },
			{ cellSize * widthRate, cellSize },
			colorWall);
		view->Show();
	}

	for (int row{ position.row }; row <= position.row + size.height; row++)
	{
		view = new View({ row, position.column * widthRate },
			{ cellSize * widthRate, cellSize },
			colorWall);
		view->Show();

		view = new View({ row, (position.column + size.width) * widthRate },
			{ cellSize * widthRate, cellSize },
			colorWall);
		view->Show();
	}
}

void SnakeGame::SnakeShow(bool visible)
{
	for(View* view : snake)
	{
		if (visible)
			view->Show();
		else
			view->Hide();
	}
}

int SnakeGame::RandRange(int low, int hi)
{
	return low + rand() % (hi - low + 1);
}

void SnakeGame::FoodShow()
{
	food->Hide();

	int row{ RandRange(position.row + 1, position.row + size.height - 1) };
	int column{ RandRange(position.column + 2, position.column + size.width - 2) };
	this->food->Move({ row, column * widthRate });

	food->Show();
}

SnakeGame::SnakeGame(Position position, Size size)
	: position{ position },
	size{ size }
{
	snakeHead = new View(
		{ this->position.row + this->size.height / 2,
			(this->position.column + this->size.width / 2) * widthRate },
		{ cellSize * widthRate, cellSize },
		colorHead);

	snake.push_back(snakeHead);

	int row{ RandRange(position.row + 1, position.row + size.height - 1) };
	int column{ RandRange(position.column + 1, position.column + size.width - 1) };

	food = new View({ row, column }, { cellSize * widthRate, cellSize }, colorFood);
}

void SnakeGame::Play()
{
	srand(time(nullptr));

	FieldShow();
	SnakeShow();
	FoodShow();
}
