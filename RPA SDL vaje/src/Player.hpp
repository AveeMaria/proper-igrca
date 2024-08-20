#pragma once

#include "Game.hpp"
#include "Entity.hpp"
#include "Map.hpp"

class Player:public Entity
{
private:
	int hp = 100;

	bool catSlot1 = false;
	bool catSlot2 = false;

	bool armorSlot = false;

	int durationOfSpeed = 500;
	int speed = 2;
	bool stepped = false;

	int score = 0;
	
	//bool ReplayOn = false;
	bool immortalMode = false;

	bool sui = false;

public:
	Player(const char* texturesheet, int x, int y);
	Player() {}

	void dol(Map* m) {
		//ce je stopu, zdej nebo pa bo drugic
		if (stepped) {
			stepped = !stepped;
			return;
		}

		SDL_Rect fRect = destRect;
		fRect.y += speed;
		if (m->landCollision(fRect)) {
			//nc nardi
		}
		else {
			ypos += speed;
			SpeedUpdate();
		}
	}

	
	void gor(Map* m) {
		//ce je stopu, zdej nebo pa bo drugic
		if (stepped) {
			stepped = !stepped;
			return;
		}

		SDL_Rect fRect = destRect;
		fRect.y -= speed;
		if (m->landCollision(fRect)) {
			//nc nardi
		}
		else {
			ypos -= speed;
			SpeedUpdate();
		}
	}

	void levo(Map* m) {

		//ce je stopu, zdej nebo pa bo drugic
		if (stepped) {
			stepped = !stepped;
			return;
		}

		SDL_Rect fRect = destRect;
		fRect.x -= speed;
		if (m->landCollision(fRect)) {

		}
		else {
			xpos -= speed;
			SpeedUpdate();
		}
	}

	void desno(Map* m) {
		//ce je stopu, zdej nebo pa bo drugic
		if (stepped) {
			stepped = !stepped;
			return;
		}

		SDL_Rect fRect = destRect;
		fRect.x += speed;
		if (m->landCollision(fRect)) {

		}
		else {
			xpos += speed;
			SpeedUpdate();
		}
	}


	void printPlayerInfo();
	
	//armor fore

	bool checkArmor() { 
		if (hp <= 100) {
			armorSlot = false;
		}
		return armorSlot;
	}

	void getArmor(int armor) {
		if (!armorSlot) {
			armorSlot = true;
			hp += armor;
		}
	}

	//cat fore

	void addCat();

	int howManyCat();

	void removeAllCat() { catSlot1 = false; catSlot1 = false; }


	//speed fore
	void setSpeed(int s) { speed = s; }
	
	void getSpeed(int amount) { speed += amount; }

	//to x korakih neha speed aplyat
	void SpeedUpdate() {
		static int stepcount = durationOfSpeed;
		stepcount--;

		if (stepcount <= 0) {
			speed = 2;
			stepcount = durationOfSpeed;
		}
	}


	//health fore
	int getHP() { return hp; }

	void SetHealth(int h) { hp = h; }

	void takeDamage(int dmg) { hp -= dmg; }

	//prever ce si crknu
	bool alive() {return hp > 0;}


	//se ubije
	void KYS() { hp = 0; sui = true; }

	void Addscore(int s) { score += s; }
	int GetScore() { return score; }


	void ToggleImmortalMode() { immortalMode = !immortalMode; }

	bool getSui() { return sui; }

	SDL_Rect GetPlayerRect() { return destRect; }
};
