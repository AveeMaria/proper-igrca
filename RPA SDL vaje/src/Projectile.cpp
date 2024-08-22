#include "Projectile.hpp"

Projectile::Projectile()
{
    objTexture = TextureManager::LoadTexture("ass/bullet.png");
    if (!objTexture) {
        std::cout << "Failed to load projectile texture\n";
    }
    xpos = 0; ypos = 0;
    targetX = 0; targetY = 0; Update();
}

Projectile::Projectile(int playerX, int playerY, int tX, int tY)
{
    objTexture = TextureManager::LoadTexture("ass/bullet.png");
    if (!objTexture) {
        std::cout << "Failed to load projectile texture\n";
    }


    xpos = playerX;
    ypos = playerY;
    targetX = tX;
    targetY = tY;

    std::cout << "[projectile] xpos:" << xpos << " ypos: " << ypos << " tx: " << targetX << " ty: " << targetY << "\n";

    Update();
}


void Projectile::moveToTarget(Map* map)
{
    //ce je stopu, zdej nebo pa bo drugic

    int dx = targetX - xpos;
    int dy = targetY - ypos;

    //zracuna kot
    float angle = atan2(dy, dx);

    //zracuna distanco
    float distance = sqrt(dx * dx + dy * dy);

    float dxNormalized = dx / distance;
    float dyNormalized = dy / distance;

    //da ne trippa zard floatov in ne premika enemyja ce je predalec od playerja
    if (distance <= 1) { return; }
    //if (distance <= 1 || (distance > triggerDistance && distance > triggerDistance + 50)) { return; }


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


void Projectile::moveToTarget()
{
    // Calculate the direction vector (dx, dy)
    float dx = targetX - xpos;
    float dy = targetY - ypos;

    // Calculate the distance to the target
    float distance = sqrt(dx * dx + dy * dy);

    // Prevent moving if we are close enough to the target
    if (distance <= 1.0f) {
        return;
    }

    // Normalize the direction vector
    float dxNormalized = dx / distance;
    float dyNormalized = dy / distance;

    // Move the projectile towards the target
    xpos += dxNormalized * speed;
    ypos += dyNormalized * speed;
}

void Projectile::Update()
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


void Projectile::Render()
{
    if (!visible) { return; }
    SDL_RenderDrawLine(Game::renderer, xpos + 16, ypos + 16 , targetX, targetY);
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}



