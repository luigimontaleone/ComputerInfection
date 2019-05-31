#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Level.h"
#include "PlayerMovement.h"
#include "EnemyMovement.h"
#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H
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
        EnemyMovement *enemyMovement;
        Map *map;
        Level *level;
        const float FPS;        
        int screenWidth;
        int screenHeight;
        bool redraw;
        bool lastOne;
        bool pressedSpaceBar;

        void initPos();
        void moveEnemy(int, bool);
        void printInfo();
    public:
        GameHandler(int, int);
        ~GameHandler();
        void Game();
};
#endif