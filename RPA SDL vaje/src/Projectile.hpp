#pragma once

#include "Game.hpp"
#include "Entity.hpp"
#include "Map.hpp"

class Projectile: public Entity {
private:
	int targetX = 0, targetY = 0;
	int speed = 2; bool showTrajectory = false;
	bool hitSmth = false;
public:
	Projectile();
	Projectile(int, int, int, int);

	void moveToTarget(Map* m);
	void Update();
	void Render();

	bool getHitSomething() { return hitSmth; }
	void hitSomething() { hitSmth = true; }
};

