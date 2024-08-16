#include "Enemy.hpp"
#include "Map.hpp"

Enemy::Enemy(const char* texturesheet, int x, int y)
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
}