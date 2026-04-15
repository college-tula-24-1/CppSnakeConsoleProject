#include "Snake.h"

Cell::Cell() : Cell(0, 0){}

Cell::Cell(int row, int column)
	: row{ row }, column{ column }{}

int& Cell::Row()
{
	return this->row;
}

int& Cell::Column()
{
	return this->column;
}

bool operator==(Cell left, Cell right)
{
	return left.row == right.row 
			&& left.column == right.column;
}

Snake::Snake(int width, int height)
	: width{ width },
	height{ height },
	rowDiff{}, 
	columnDiff{}
{
	head.Column() = this->width / 2;
	head.Row() = this->height / 2;
	snake.push_back(head);
}

Cell& Snake::Head()
{
	return this->head;
}

Cell Snake::Move(SnakeWay way, bool grow)
{
	switch (way)
	{
	case SnakeWay::Left:
		rowDiff = 0;
		columnDiff = -1;
		break;
	case SnakeWay::Right:
		rowDiff = 0;
		columnDiff = 1;
		break;
	case SnakeWay::Up:
		rowDiff = -1;
		columnDiff = 0;
		break;
	case SnakeWay::Down:
		rowDiff = 1;
		columnDiff = 0;
		break;
	default:
		break;
	}

	head.Row() += rowDiff;
	head.Column() + columnDiff;

	snake.insert(snake.begin(), head);

	if (!grow)
		snake.pop_back();

	return head;
}

size_t Snake::Size()
{
	return snake.size();
}

Cell Snake::At(int index)
{
	return snake[index];
}

bool Snake::Fault()
{
	if (head.Row() <= 0 || head.Row() >= height
		|| head.Column() <= 0 || head.Column() >= width)
		return true;
	for (int i{ 1 }; i < snake.size(); i++)
		if (head == snake[i])
			return true;
	return false;
}
