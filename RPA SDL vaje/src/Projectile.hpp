#pragma once

#include "Game.hpp"
#include "Entity.hpp"
#include "Map.hpp"

class Projectile: public Entity {
private:
	int targetX = 0, targetY = 0;
	int speed = 2;
public:
	Projectile();
	Projectile(int, int, int, int);

	void moveToTarget(Map* m);
	void moveToTarget();
	void Update();
	void Render();
};

