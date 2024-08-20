#include "HurtCam.hpp"

HurtCam::HurtCam(const char* texturesheet, int x, int y)
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
    visible = false;
    Update();
}


HurtCam::HurtCam()
{
    objTexture = TextureManager::LoadTexture("ass/hurtcam.png");
    xpos = 0;
    ypos = 0;
    visible = false;
    Update();
}


void HurtCam::Update()
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
