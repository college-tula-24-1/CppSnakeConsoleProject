#pragma once
#include <string>
#include <vector>
#include <Windows.h>

struct Position
{
	int row;
	int column;
};

struct Size
{
	int width;
	int height;
};

enum class Color
{
	Black,
	DarkBlue,
	DarkGreen,
	DarkCyan,
	DarkRed,
	DarkMagenta,
	DarkYellow,
	Gray,
	DarkGray,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Yellow,
	White
};

class Console
{
	HANDLE inputConsole;
	HANDLE outputConsole;

public:
	Console();

	void CursorPosition(Position position);
	void Write(std::string message);
	void WritePosition(Position position, std::string message);

	HANDLE OutputConsole();

	void CursorVisible(bool visible = true);

	std::vector<INPUT_RECORD> ReadEvents();
};

