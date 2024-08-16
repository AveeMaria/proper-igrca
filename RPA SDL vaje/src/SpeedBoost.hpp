#pragma once
#include "Entity.hpp"

class SpeedBoost : public Entity {
private:
	int speed = 1;
public:
	SpeedBoost() { objTexture = TextureManager::LoadTexture("ass/speed_boost.png"); }
	SpeedBoost(int x, int y);
	
	int returnSpeed() { return speed; }
};