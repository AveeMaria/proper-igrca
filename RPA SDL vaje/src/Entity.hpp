#pragma once

#include "Game.hpp"
#include "TextureManager.hpp"

class Entity {
protected:
	static int entityCount;

	int xpos;
	int ypos;

	bool visible = true;

	SDL_Texture* objTexture;

	SDL_Rect srcRect, destRect, drawRect;

public:
	static bool showHitboxes;
	Entity(const char* texturesheet,int x,int y);
	Entity() {
		xpos = 0;
		ypos = 0;
		entityCount++;
		Update();
	}
	~Entity();

	static int getEntityCount() { return entityCount; }

	float distance(int, int);

	int getX() { return xpos; }
	int getY() { return ypos; }

	//ZA COLLISIONE!!!!!!
	SDL_Rect getDestRect() { return destRect; }

	//ce spremenis destrect spremenis tud xpos&ypos da ga update() ne unic
	void setDestRect(SDL_Rect rect) { destRect = rect; xpos = rect.x; ypos = rect.y; }

	void setVisible(bool s) { visible = s; }

	bool getVisible() { return visible; }


	virtual void setXY(int, int);

	virtual void Update();
	virtual void Render();
	bool rectCollision(SDL_Rect);
};