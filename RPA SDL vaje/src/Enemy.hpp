#pragma once

#include "Game.hpp"
#include "Entity.hpp"
#include "Map.hpp"

class Enemy: public Entity {
private:

	int hp = 100;
	
	int dmg = 2;
	

	int speed = 2;

	bool stepped = false;

	int triggerDistance = 200;

public:
	Enemy(const char* texturesheet, int x, int y);
	Enemy() {}

	void setDmg(int d) {
		dmg = d; 
	}

	int doDamage() {
		static short debounce = 5;

		debounce--;
		if (debounce <= 0) {
			debounce = 5;
			return dmg;
		}
		return 0;
	}

	int getDmgValue() { return dmg; }

	void moveToCoordinate(float, float, Map* map);

	void takeDamage(int dmg) { hp -= dmg; }

	bool isAlive() { return hp > 0; }
};