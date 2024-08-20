#include "Entity.hpp"
#include "TextureManager.hpp"

Entity::Entity(const char* texturesheet, int x, int y) 
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
}


//does nothing
Entity::~Entity() 
{
    SDL_DestroyTexture(objTexture);
}

//zracuna dolzino
float Entity::distance(int X, int Y)
{
    int dx = X - xpos;
    int dy = Y - ypos;
    
    return (float)sqrt(dx * dx + dy * dy);    
}

void Entity::setXY(int x,int y) {
    xpos = x; ypos = y;
}

void Entity::Update()
{
    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}

void Entity::Render()
{
    if (!visible) { return; }
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}


bool Entity::rectCollision(SDL_Rect rect)
{
    //to prever ce se dva recta prekrivata(collidata)
    return SDL_HasIntersection(&rect, &destRect);
}
