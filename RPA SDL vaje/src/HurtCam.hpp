#pragma once

#include "Game.hpp"
#include "Entity.hpp"

class HurtCam: public Entity {
private:
public:
	HurtCam(const char* texturesheet, int x, int y);
	HurtCam();

	void Update();
};