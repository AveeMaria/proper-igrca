#pragma once

#include "Game.hpp"
#include "Entity.hpp"
#include "Map.hpp"

class Enemy :public Entity {
private:
	int hp = 100;

public:
	Enemy(const char* texturesheet, int x, int y);
	Enemy() {}

};