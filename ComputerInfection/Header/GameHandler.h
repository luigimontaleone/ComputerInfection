#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Level.h"
#include "PlayerMovement.h"
#include "EnemyMovement.h"

/*Gestore principale del gioco */
class GameHandler
{
    private:
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_KEYBOARD_STATE currently;
    ALLEGRO_FONT *font;
    ALLEGRO_TIMER *timer;

    Player *player;
    PlayerMovement *playerMovement;
    Enemy *boss;
    vector<Enemy*> enemies;
    list<Entity*> bonus;
    EnemyMovement *enemyMovement;
    Map *map;
    Level *level;

    const float FPS;        
    int screenWidth;
    int screenHeight;
    int bonusKilled;
    bool redraw;
    bool lastOne;
    bool pressedSpaceBar;

    void initPos();
    void printInfo() const;
    void spawnBonus();
    void checkBonus();

    public:
    GameHandler(int, int);
    ~GameHandler();
    void Game();
};
#endif