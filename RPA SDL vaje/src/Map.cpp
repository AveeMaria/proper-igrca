#include "Map.hpp"
#include "TextureManager.hpp"

int lvl1[20][30] = {
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,1,1,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
    { 1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1 },
    { 1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1 },
    { 1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1 },
    { 1,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1 },
    { 1,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1 },
    { 1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,1,1 }
};

Map::Map() {

    ////////////////FAKING SPREMINJAM SPET FILEPATH

    tile = TextureManager::LoadTexture("ass/tile.png");
    wall = TextureManager::LoadTexture("ass/wall.png");
    door = TextureManager::LoadTexture("ass/door.png");
    exit = TextureManager::LoadTexture("ass/red.png");

    LoadMap(lvl1);
    wallMarker(lvl1);

    src.x = src.y = 0;
    dest.x = dest.y = 0;

    src.w = dest.w = 32;
    src.h = dest.h = 32;
}

Map::~Map() {}

void Map::LoadMap(int arr[20][30]) {

    for (int row = 0; row < 20; row++) {
        for (int column = 0; column < 30; column++) {
            map[row][column] = arr[row][column];
        }
    }
}

void Map::DrawMap() {

    int type = 0;

    for (int row = 0; row < 20; ++row) {
        for (int column = 0; column < 30; ++column) {

            type = map[row][column];

            dest.x = column * 32;
            dest.y = row * 32;

            switch (type)
            {
            case 0:
                TextureManager::Draw(tile, src, dest);
                break;
            case 1:
                TextureManager::Draw(wall, src, dest);
                break;
            case 2:
                TextureManager::Draw(door, src, dest);
                break;
            default:
                TextureManager::Draw(exit, src, dest);
                break;
            }
        }
    }
}

SDL_Rect Map::validSpawn()
{
    SDL_Rect spawn{ 0,0,32,32 };

    int rX = 0;
    int rY = 0;

    do {
        //eno mnj kr spodn in desen wall
        rX = rand() % 29;
        rY = rand() % 19;

        //std::cout << "trying: " << rX << " " << rY << "\n";

    }while (lvl1[rY][rX] != 0);

    spawn.x = rX * 32;
    spawn.y = rY * 32;    

    //std::cout << "spawned at: " << spawn.x << " " << spawn.y << "\n\n";
    

    return spawn;  
}

void Map::wallMarker(int map[20][30])
{
    zidovi.clear();
    SDL_Rect a{ 0, 0, 32, 32 };
    for (int row = 0; row < 30; ++row) {
        for (int column = 0; column < 20; ++column) {
            if (map[column][row] != 0 && map[column][row] != 2) {
                a.x = row * 32;
                a.y = column * 32;

                zidovi.push_back(a);
                //std::cout << a.x << " " << a.y << "\n";
            }
        }
    }
}

//kle se playerrect posle kot "e"
bool Map::landColision(SDL_Rect e)
{
    //prever collision z usemi zidovi   

    for (SDL_Rect &z : zidovi) {
        if (SDL_HasIntersection(&z, &e)) {
            return true;
        }
    }
    return false;
}

//za debugat collision errorje
void Map::highLightWalls()
{
    //return;

    for (SDL_Rect &z : zidovi) {
        SDL_RenderDrawRect(Game::renderer, &z);
    }
}