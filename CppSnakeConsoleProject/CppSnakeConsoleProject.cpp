#include <iostream>
#include "SnakeGame.h"

int main()
{
	SnakeGame* game = new SnakeGame(5, 5, 30, 20);
	game->Play();
}
