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
	static HANDLE inputConsole;
	static HANDLE outputConsole;

public:

	static void Background(Color color);
	static void Foreground(Color color);

	static void CursorPosition(Position position);
	static void Write(std::string message);
	static void WritePosition(Position position, std::string message);

	static void CursorVisible(bool visible = true);

	static std::vector<INPUT_RECORD> ReadEvents();
};

