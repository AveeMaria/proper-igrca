#include "Game.hpp"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	srand(static_cast<unsigned int>(time(nullptr)));

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("okncek", 960, 640, false);


	while (game->running())
	{
		frameStart = SDL_GetTicks();
		
		game->handleEvents();
		if (!game->isPaused()) {
			game->update();
			game->render();
		}

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	delete game;
	return 0;
}