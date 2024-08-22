#include "Game.hpp"
#include "TextureManager.hpp"
#include "Entity.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Zivalca.hpp"
#include "BodyArmor.hpp"
#include "SpeedBoost.hpp"
#include "Inventory.hpp"
#include "HurtCam.hpp"
#include "SerialPort.hpp"
#include "Projectile.hpp"



SerialPort serial("COM3", CBR_9600);

Player* player;
Inventory* inventory;
HurtCam* hurtcam;



BodyArmor* bodyarmor;

std::vector<Projectile*> projectiles;

std::vector<Zivalca*> zivalce;

std::vector<Enemy*> enemies;

std::vector<SpeedBoost*> speedboosts;

Map* map;

SDL_Renderer* Game::renderer = nullptr;
int Entity::entityCount = 0;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            drawLoadingScreen();
		}

		isRunning = true;
	}

	player = new Player("ass/player.png", 64, 64);
	map = new Map();
    bodyarmor = new BodyArmor();
    bodyarmor->setDestRect(map->validSpawn());
    
    hurtcam = new HurtCam();
    hurtcam->setVisible(false);

    inventory = new Inventory();

    bodyarmor->Update();

    spawnSpeedBoosts(2);

    spawnZivalice(4);

    spawnEnemies(3);
}

void Game::handleEvents() {
    SDL_PumpEvents();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                std::cout << "klik na: [" << mouseX << ", " << mouseY << "]\n";
                Projectile* p = new Projectile(player->getX(), player->getY(), mouseX, mouseX);
                projectiles.push_back(p);
                //projman->spawnProjectile(player->getX(), player->getY(), mouseX, mouseX);
            }
            break;

        default:
            break;
        }
    }


    //joystick movement
    if (joystickmode) {
        std::string serialData = serial.readLine();
        std::istringstream stream(serialData);

        int xValue = 0, yValue = 0;
        bool buttonPressed = false;
        std::string token;

        try {
            if (std::getline(stream, token, ';')) {
                xValue = std::stoi(token);
                xValue /= 10;
            }

            if (std::getline(stream, token, ';')) {
                yValue = std::stoi(token);
                yValue /= 10;
            }

            if (std::getline(stream, token, ';')) {
                buttonPressed = token == "1";
            }

            //std::cout << "X: " << xValue << ", Y: " << yValue << ", Button: " << (buttonPressed ? "0\n" : "1\n");


            if (xValue < 40 && xValue > 20) {
                //std::cout << "levo\n";
                player->levo(map);
            }
            else if (xValue <= 20) {
                //std::cout << "2levo\n";
                //player->levo(map);
                player->levo(map);
            }

            if (xValue > 60 && xValue < 80) {
                //std::cout << "desno\n";
                player->desno(map);
            }
            else if (xValue >= 80) {
                //std::cout << "2desno\n";
                //player->desno(map);
                player->desno(map);
            }


            if (yValue < 40 && yValue > 20) {
                //std::cout << "gor\n";
                player->gor(map);
            }
            else if (yValue <= 20) {
                //std::cout << "2gor\n";
                //player->gor(map);
                player->gor(map);
            }

            if (yValue > 60 && yValue < 80) {
                //std::cout << "2dol\n";
                player->dol(map);
            }
            else if (yValue >= 80) {
                //std::cout << "dol\n";
                //player->dol(map);
                player->dol(map);
            }

        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << e.what() << '\n';
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Out of range: " << e.what() << '\n';
        }
    }


    //keyboard movement
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_ESCAPE]) {
        isRunning = false;
    }

    if (currentKeyStates[SDL_SCANCODE_E]) {
        //inventory
        inventory->toggleInventory();
        if (inventory->showInventory()) {
            paused = true;
        }
        else {
            paused = false;
        }
    }

    if (inventory->showInventory()) {

        inventory->Render(); 
        update();
        render();
        
        return;
    }

    if (currentKeyStates[SDL_SCANCODE_W]) {
        player->gor(map);
    }

    if (currentKeyStates[SDL_SCANCODE_S]) {
        player->dol(map);
    }

    if (currentKeyStates[SDL_SCANCODE_A]) {
        player->levo(map);
    }

    if (currentKeyStates[SDL_SCANCODE_D]) {
        player->desno(map);
    }

    if (currentKeyStates[SDL_SCANCODE_X]) {
        player->KYS();//samomor
    }


    if (currentKeyStates[SDL_SCANCODE_L]) {
        std::cout << Entity::getEntityCount() << "\n";
    }
    
    if (currentKeyStates[SDL_SCANCODE_I]) {
        player->setHealth(2147483647);
    }

    //player info
    if (currentKeyStates[SDL_SCANCODE_F3]) {
        player->printPlayerInfo();
    }
}

void Game::update() {

    if (inventory->showInventory()) {
        inventory->Update();
        return;
    }
    if (!player->alive()) {
        isRunning = false;
    }

    player->Update();
   
    for (Projectile* p : projectiles) {
        p->moveToTarget(map);
    }
    
    for (Projectile* p : projectiles) {
        p->Update();
    }

    if (!player->checkArmor()) {
        if (bodyarmor->rectCollision(player->GetPlayerRect()) && !bodyarmor->getUsed()) {
            player->getArmor(bodyarmor->getDefensePoints());
            bodyarmor->setSetUsed(true);
            std::cout << "dubu armor!\n";
        }
    }
    else {
        if (player->checkArmor()) {
            //bodyarmor->setDestRect(player->getDestRect()); // mnj efficient
            bodyarmor->setXY(player->getX(), player->getY());
            bodyarmor->Update();

            //std::cout << "mam armor!\n";
        }
    }
    
    if(player->getHP() <= 100 && bodyarmor->getUsed()) {
        bodyarmor->changeToBrokenTexture();
    }

    {
    bool noCollision = true;
    for (Enemy* e : enemies) {
        e->moveToCoordinate(player->getX(), player->getY(), map);
        e->Update();
        

        if (e->rectCollision(player->getDestRect())) {
            //std::cout << "collided\n";
            ///neki ne dela kle
            player->takeDamage(/*e->doDamage()*/1);
            hurtcam->setVisible(true);
            noCollision = false;
        }


        hurtcam->Update();

        //e->moveTowardsPlayer(player->getX(), player->getY(), map);

    }

    if (noCollision) {
        hurtcam->setVisible(false);
    }
    }

    // sam z iteratorjem loh brises stvari (z foreach nemores)
    for (auto it = zivalce.begin(); it != zivalce.end(); ++it) { //it je kot i v foorloopu, gre od zacetka do konca vektorja
        
        Zivalca* z = *it;

        if (z->rectCollision(player->getDestRect())) {

            if (player->howManyCat() < 2) {

                player->addCat();

                zivalce.erase(it);//zato mamo iterator
                
                //std::cout << "cat: " << player->howManyCat() << "\n";
                    
                break;//to nardi da ne crasha kr k deletas iterator nemors vec loopat z iteratorjem po vektorju!
            }          
        }
    }

    for (Zivalca* z : zivalce) {
        z->Update();
    }

    for (auto it = speedboosts.begin(); it != speedboosts.end(); ++it) {
        SpeedBoost* s = *it;

        if (s->rectCollision(player->getDestRect())) {
            player->getSpeed(s->returnSpeed());

            speedboosts.erase(it);
            break;//to nardi da ne crasha kr k deletas iterator nemors vec loopat z iteratorjem po vektorju!
        }
    }

    for (SpeedBoost* s : speedboosts) {
        s->Update();
    }

    
}

void Game::render() {
	SDL_RenderClear(renderer);

    if (inventory->showInventory()) {
        inventory->Render();
        SDL_RenderPresent(renderer);
        return;
    }

	map->DrawMap();
    map->highLightWalls();
    

    for (SpeedBoost* s : speedboosts) {
        s->Render();
    }

    for (Zivalca* z : zivalce) {
        z->Render();
    }

    for (Enemy* e : enemies) {
        e->Render();
    }
    
    player->Render();
    bodyarmor->Render();

    for (Projectile* p : projectiles) {
        p->Render();
    }

    if (hurtcam->getVisible()) {
        hurtcam->Render();
    }

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "game cleaned\n";
}

void Game::drawLoadingScreen()
{
    SDL_Texture* objTexture = TextureManager::LoadTexture("ass/loading.png");

    SDL_Rect srcRect{ 0,0,1920,1280 };
    SDL_Rect destRect{ 0,0, 960, 640 };
    
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
    SDL_RenderPresent(Game::renderer);
}

void Game::spawnZivalice(short st)
{
    zivalce.clear();
    SDL_Rect spawn;
    for (int i = 0; i < st; i++) {
        spawn = map->validSpawn();
        Zivalca* z = new Zivalca("ass/cat.png",spawn.x,spawn.y);

        zivalce.push_back(z);//emplace back rab konstruktor parametre kr sam ve ker dejtatype gor daje
    }
}

void Game::spawnEnemies(short st) {
    enemies.clear();
    SDL_Rect spawn;
    
    for (int i = 0; i < st; i++) {
        
        spawn = map->validSpawn();
        Enemy* e = new Enemy("ass/enemy.png", spawn.x, spawn.y);

        enemies.push_back(e);
    }
}

void Game::spawnSpeedBoosts(short st) {
    speedboosts.clear();
    SDL_Rect spawn;

    for (int i = 0; i < st; i++) {

        spawn = map->validSpawn();
        SpeedBoost* s = new SpeedBoost(spawn.x, spawn.y);

        speedboosts.push_back(s);
        speedboosts[i]->Update();
    }
}