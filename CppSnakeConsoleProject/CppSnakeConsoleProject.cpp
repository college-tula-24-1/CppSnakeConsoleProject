#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

#include "SnakeGame.h"

int main()
{
	SnakeGame game({ 5, 10 });
	game.Play();
}
