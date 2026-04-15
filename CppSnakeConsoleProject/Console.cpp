#include "Console.h"

HANDLE Console::inputConsole = GetStdHandle(STD_INPUT_HANDLE);
HANDLE Console::outputConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Console::Background(Color color)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(outputConsole, &info);

	WORD colorCurrent{ info.wAttributes };
	WORD colorNew = (colorCurrent & 0b1111) | (unsigned char)color << 4;

	SetConsoleTextAttribute(outputConsole, colorNew);
}

void Console::Foreground(Color color)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(outputConsole, &info);

	WORD colorCurrent{ info.wAttributes };
	WORD colorNew = ((colorCurrent >> 4) << 4) | (unsigned char)color;

	SetConsoleTextAttribute(outputConsole, colorNew);
}

void Console::CursorPosition(Position position)
{
	COORD coord{ position.column, position.row };
	SetConsoleCursorPosition(outputConsole, coord);
}

void Console::Write(std::string message)
{
	LPDWORD writted{};
	WriteConsoleA(outputConsole,
		message.c_str(),
		message.length(),
		writted,
		nullptr);
}

void Console::WritePosition(Position position, std::string message)
{
	CursorPosition(position);
	Write(message);
}

void Console::CursorVisible(bool visible)
{
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(outputConsole, &info);
	info.bVisible = visible;
	SetConsoleCursorInfo(outputConsole, &info);
}

std::vector<INPUT_RECORD> Console::ReadEvents()
{
	std::vector<INPUT_RECORD> events;
	
	DWORD eventsCount{};
	DWORD eventsReadedCount{};

	GetNumberOfConsoleInputEvents(inputConsole, &eventsCount);
	if (eventsCount)
	{
		events.clear();
		events.resize(eventsCount);
		ReadConsoleInputA(inputConsole,
			events.data(),
			eventsCount,
			&eventsReadedCount);
	}
	return events;
}
