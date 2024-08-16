#include "SpeedBoost.hpp"

SpeedBoost::SpeedBoost(int x, int y)
{
	objTexture = TextureManager::LoadTexture("ass/speed_boost.png");
	xpos = x;
	ypos = y;
}