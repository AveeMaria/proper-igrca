#include "Enemy.hpp"
#include "Map.hpp"

Enemy::Enemy(const char* texturesheet, int x, int y)
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
}
/*
//#prekopiran iz prejsnga gejma
void Enemy::moveTowardsPlayer(float PlayerPosX, float PlayerPosY, Map* map) {
    float dx = PlayerPosX - xpos;
    float dy = PlayerPosY - ypos;

    //zracuna kot
    float angle = atan2(dy, dx);

    //zracuna distanco
    float distance = sqrt(dx * dx + dy * dy);

    float dxNormalized = dx / distance;
    float dyNormalized = dy / distance;

    //da ne trippa zard floatov in ne premika enemyja ce je predalec od playerja
    if (distance <= 1 || (distance > triggerDistance && distance > triggerDistance + 50)) { return; }


    float tempX = xpos + speed * dxNormalized;
    float tempY = ypos + speed * dyNormalized;

    SDL_Rect enemyDestRect = {
        (int)tempX,
        (int)tempY,
        srcRect.w,
        srcRect.h
    };

    //preveri da negre enemy izven okna
    if (tempX >= 0 && tempX + srcRect.w <= 960 && tempY >= 0 && tempY + srcRect.h <= 640) {
        //preveri land collision
        if (!map->landCollision(enemyDestRect)) {
            xpos = tempX;
            ypos = tempY;
        }
    }
}
*/
void Enemy::moveToCoordinate(float destX, float destY, Map* map) {
    //ce je stopu, zdej nebo pa bo drugic
    
    if (stepped) {
        stepped = !stepped;
        return;
    }

    float dx = destX - xpos;
    float dy = destY - ypos;

    //zracuna kot
    float angle = atan2(dy, dx);

    //zracuna distanco
    float distance = sqrt(dx * dx + dy * dy);

    float dxNormalized = dx / distance;
    float dyNormalized = dy / distance;

    //da ne trippa zard floatov in ne premika enemyja ce je predalec od playerja
    if (distance <= 1 || (distance > triggerDistance && distance > triggerDistance + 50)) { return; }


    float tempX = xpos + speed * dxNormalized;
    float tempY = ypos + speed * dyNormalized;

    SDL_Rect fRect = {
        (int)tempX,
        (int)tempY,
        srcRect.w,
        srcRect.h
    };

    //preveri da negre enemy izven okna
    //if (tempX >= 0 && tempX + srcRect.w <= 800 && tempY >= 0 && tempY + srcRect.h <= 600) {
        //preveri land collision
        if (!map->landCollision(fRect)) {
            xpos = tempX;
            ypos = tempY;
        }
    //}
}