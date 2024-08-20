#pragma once
#include "Game.hpp"

class Map {
public:
    Map();
    ~Map();

    void LoadMap(int arr[20][30]);
    void DrawMap();

    SDL_Rect validSpawn();

    //nardi SDL recte na usak wall in da u vector
    void wallMarker(int map[20][30]);

    //prever collision nekga entityja
    bool landCollision(SDL_Rect e);

    void highLightWalls();
       
private:
    SDL_Rect src, dest;

    SDL_Texture* tile;
    SDL_Texture* wall;
    SDL_Texture* door;
    SDL_Texture* exit;

    std::vector<SDL_Rect> zidovi;
    std::vector<SDL_Rect> takenSpawns;

    int map[20][30];
};