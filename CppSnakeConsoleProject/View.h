#pragma once
#include "Console.h"

class View
{
	Position position;
	Size size;
	Color background;
	Color foreground;

	bool visible;

	CHAR_INFO* bufferView;
	CHAR_INFO* bufferSave;

	static Console console;
public:
	View(Position position,
		Size size,
		Color background = Color::Black,
		Color foreground = Color::White);
	~View();

	friend bool operator==(View left, View right);

	void Move(Position position);

	void Show();
	void Hide();
};

