#include "Enemy.hpp"

class BodyArmor : public Entity {
private:
	int defense = 100;
	bool used = false;
public:
	BodyArmor() { objTexture = TextureManager::LoadTexture("ass/body_armor.png"); }
	BodyArmor(int x, int y);

	//vnre kok defense pointov dobis

	bool getUsed() { return used; }

	void setSetUsed(bool u) { used = u; }

	void changeToBrokenTexture() {
		objTexture = TextureManager::LoadTexture("ass/body_armor_broken.png");
	}

	int getDefensePoints() { return defense; }
};