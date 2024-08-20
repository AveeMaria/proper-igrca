#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_main.h"
#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <iostream>
#include <sstream>  // For std::istringstream


class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	bool isPaused() { return paused; }


	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }

	void drawLoadingScreen();


	void spawnZivalice(short);

	void spawnEnemies(short);

	void spawnSpeedBoosts(short);

	static SDL_Renderer* renderer;
	//bool GetHitboxes() { return showHitboxes; }
	//bool showHitboxes =false;

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
private:

	bool isRunning = false;
	bool paused = false;

	uint32_t cnt = 0;
	SDL_Window* window;
};