#include "BodyArmor.hpp"

BodyArmor::BodyArmor(int x, int y)
{
	objTexture = TextureManager::LoadTexture("ass/body_armor.png");
	xpos = x;
	ypos = y;
}
