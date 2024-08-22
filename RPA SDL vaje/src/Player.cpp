#include "Player.hpp"
#include "Map.hpp"

Player::Player(const char* texturesheet, int x, int y)
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
}

void Player::printPlayerInfo()
{
    std::cout << "[Player info]\n";

    std::cout << "x: " << xpos << "y: " << ypos << "\n";
    std::cout << "hp: " << hp << ", armor: ";

    if (armorSlot) {
        std::cout << "true\n";
    }
    else {
        std::cout << "false\n";
    }
    std::cout << "cat amount: " << howManyCat() << "\n\n";
}

void Player::addCat()
{
    //ce ma 0 catov dobi enga in neha funkcijo
    if (catSlot1 == false) {
        catSlot1 = true;
        return;
    }

    //cene doda na konc en cat in nc vec
    if (catSlot2 == false) {
        catSlot2 = true;
        return;
    }
}

int Player::howManyCat()
{
    int catNum = 0;

    if (catSlot1) { catNum++; }

    if (catSlot2) { catNum++; }

    return catNum;
}