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
			{ (rowStart + row) * cellSize + i, 
			  (columnStart + column) * cellSize * widthRate },
			cellStr);
}

void SnakeGame::FieldShow()
{

	for (int row{ -1 }; row <= height + 1; row++)
	{
		CellShow(row, -1, wallFieldColor);
		CellShow(row, width + 1, wallFieldColor);
	}

	for (int column{ -1 }; column <= width + 1; column++)
	{
		CellShow(-1, column, wallFieldColor);
		CellShow(height + 1, column, wallFieldColor);
	}
}

void SnakeGame::FoodShow()
{
	food = new Cell(RandomRange(0, height), RandomRange(0, width));
	CellShow(food->Row(), food->Column(), foodColor);
}

void SnakeGame::SnakeShow(bool visible)
{
	Color color;
	for (int i{}; i < snake->Size(); i++)
	{
		if (visible)
			color = (i) ? snakeBodyColor : snakeHeadColor;
		else
			color = backFieldColor;
		CellShow(snake->At(i).Row(), snake->At(i).Column(), color);
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
	srand(time(nullptr));

	FieldShow();
	FoodShow();
	SnakeShow();

	bool isGame{ true };
	bool isEat{ false };

	SnakeWay way{ SnakeWay::Stop };

	while (true)
	{
		auto events = Console::ReadEvents();

		for (auto event : events)
		{
			if (event.EventType == KEY_EVENT)
			{
				auto keyCode = event.Event.KeyEvent.wVirtualKeyCode;
				

				switch (keyCode)
				{
				case VK_LEFT:
					way = SnakeWay::Left;
					break;
				case VK_RIGHT:
					way = SnakeWay::Right;
					break;
				case VK_UP:
					way = SnakeWay::Up;
					break;
				case VK_DOWN:
					way = SnakeWay::Down;
					break;
				case VK_ESCAPE:
					isGame = false;
					break;
				default:
					break;
				}
			}
			
			if (!isGame)
				break;
			if (snake->Fault())
			{
				isGame = false;
				break;
			}

			SnakeShow(false);
			isEat = snake->Head() == *food;
			snake->Move(way, isEat);
			SnakeShow();

		}
		if (!isGame)
			break;
	}
}

SnakeGame::~SnakeGame()
{
	delete snake;
	delete food;
}
