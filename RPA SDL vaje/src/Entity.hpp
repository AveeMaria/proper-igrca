#pragma once

#include "Game.hpp"
#include "TextureManager.hpp"

class Entity {
protected:
	int xpos=0;
	int ypos=0;

	SDL_Texture* objTexture;

	SDL_Rect srcRect, destRect, drawRect;

public:
	static bool showHitboxes;
	Entity(const char* texturesheet,int x,int y);
	Entity() {}
	~Entity();

	float distance(int, int);

	int getX() { return xpos; }
	int getY() { return ypos; }

	//ZA COLLISIONE!!!!!!
	SDL_Rect getDestRect() { return destRect; }

	//ce spremenis destrect spremenis tud xpos&ypos da ga update() ne unic
	void setDestRect(SDL_Rect rect) { destRect = rect; xpos = rect.x; ypos = rect.y; }

	virtual void setXY(int, int);

	void Update();
	void Render();
	bool rectCollision(SDL_Rect rect);
};