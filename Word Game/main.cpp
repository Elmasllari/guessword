#include "Game.h"

int main()
{
	std::unique_ptr<Game> game = std::make_unique<Game>();

	game->Run();


	std::cin.get();
	return 0;
}