#include "Zivalca.hpp"

Zivalca::Zivalca(const char* texturesheet, int x, int y)
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
}

Zivalca::Zivalca()
{
    objTexture = TextureManager::LoadTexture("ass/cat.png");
}
