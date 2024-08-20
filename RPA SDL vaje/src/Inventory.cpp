#include "Inventory.hpp"

Inventory::Inventory(const char* texturesheet, int x, int y)
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;

    Update();
}

Inventory::Inventory()
{
    objTexture = TextureManager::LoadTexture("ass/inventory.png");
    xpos = 0;
    ypos = 0;

    Update();
}

void Inventory::Update()
{    
    srcRect.h = 640;
    srcRect.w = 960;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = 0;
    destRect.y = 0;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}
