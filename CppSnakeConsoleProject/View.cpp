#include "View.h"

Console View::console;

View::View(Position position, Size size, Color background, Color foreground)
	: position{ position },
	size{ size },
	background{ background },
	foreground{ foreground },
	visible{ false }
{
	WORD attributes{ (WORD)((WORD)this->background << 4 | (WORD)this->foreground) };
	bufferView = new CHAR_INFO[this->size.width * this->size.height];
	for (int i{}; i < this->size.width * this->size.height; i++)
	{
		bufferView[i].Char.AsciiChar = ' ';
		bufferView[i].Attributes = attributes;
	}

	bufferSave = new CHAR_INFO[this->size.width * this->size.height];
	COORD bufferSaveSize{ this->size.width, this->size.height };
	COORD bufferSavePosition{ 0, 0 };
	SMALL_RECT screenPosition{ this->position.column,
		this->position.row,
		this->position.column + this->size.width,
		this->position.row + this->size.height };

	ReadConsoleOutputA(
		console.OutputConsole(),
		this->bufferSave,
		bufferSaveSize,
		bufferSavePosition,
		&screenPosition);
}

View::~View()
{
	delete[] bufferView;
	delete[] bufferSave;
}

void View::Move(Position position)
{
	this->position = position;
	
	delete[] this->bufferSave;
	this->bufferSave = new CHAR_INFO[this->size.width * this->size.height];

	COORD bufferSaveSize{ this->size.width, this->size.height };
	COORD bufferSavePosition{ 0, 0 };
	SMALL_RECT screenPosition{ this->position.column,
		this->position.row,
		this->position.column + this->size.width,
		this->position.row + this->size.height };

	ReadConsoleOutputA(
		console.OutputConsole(),
		this->bufferSave,
		bufferSaveSize,
		bufferSavePosition,
		&screenPosition);

}

void View::Show()
{
	if (!visible)
	{
		COORD bufferViewSize{ this->size.width, this->size.height };
		COORD bufferViewPosition{ 0, 0 };
		SMALL_RECT screenPosition{ this->position.column,
			this->position.row,
			this->position.column + this->size.width,
			this->position.row + this->size.height };

		WriteConsoleOutputA(
			console.OutputConsole(),
			bufferView,
			bufferViewSize,
			bufferViewPosition,
			&screenPosition);

		visible = true;
	}
}

void View::Hide()
{
	if (visible)
	{
		COORD bufferSaveSize{ this->size.width, this->size.height };
		COORD bufferSavePosition{ 0, 0 };
		SMALL_RECT screenPosition{ this->position.column,
			this->position.row,
			this->position.column + this->size.width,
			this->position.row + this->size.height };

		WriteConsoleOutputA(
			console.OutputConsole(),
			bufferSave,
			bufferSaveSize,
			bufferSavePosition,
			&screenPosition);

		visible = false;
	}
}

bool operator==(View left, View right)
{
	return left.position.row == right.position.row
		&& left.position.column == right.position.column;
}
