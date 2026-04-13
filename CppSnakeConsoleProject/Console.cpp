#include "Console.h"

Console::Console()
	: inputConsole{ GetStdHandle(STD_INPUT_HANDLE) },
	outputConsole{ GetStdHandle(STD_OUTPUT_HANDLE) }{}

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

HANDLE Console::OutputConsole()
{
	return outputConsole;
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
