#include <iostream>
#include "SnakeGame.h"

int main()
{
	SnakeGame* game = new SnakeGame(2, 5, 20, 10);
	game->Play();
}
