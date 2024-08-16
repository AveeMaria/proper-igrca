#include "Enemy.hpp"

class BodyArmor : public Entity {
private:
	int defense = 100;

public:
	BodyArmor() { objTexture = TextureManager::LoadTexture("ass/body_armor.png"); }
	BodyArmor(int x, int y);

	//vnre kok defense pointov dobis
	int getDefensePoints() { return defense; }
};