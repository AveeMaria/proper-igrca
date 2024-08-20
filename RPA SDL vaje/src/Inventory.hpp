#pragma once

#include "Game.hpp"
#include "Entity.hpp"
#include "Map.hpp"


class Inventory: public Entity {
private:
	bool show = false;
public:
	Inventory(const char* texturesheet, int x, int y);
	Inventory();

	void Update();

	void toggleInventory() { 
		static short debounceTime = 6;
		
		debounceTime--;

		if (debounceTime <= 0) {
			show = !show;
			std::cout << "inventory: " << show << "\n";
			debounceTime = 6;
		}
	}

	bool showInventory() { return show; }
};