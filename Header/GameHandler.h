#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "CollisionHandler.h"
#include "BorderHandler.h"
#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H
class GameHandler
{
    private:
        ALLEGRO_EVENT_QUEUE *event_queue;
        ALLEGRO_DISPLAY_MODE disp_data;
        ALLEGRO_TRANSFORM trans;
        ALLEGRO_DISPLAY *display;
        ALLEGRO_KEYBOARD_STATE currently;
        ALLEGRO_FONT *font;
        ALLEGRO_TIMER *timer;
        Player *player;
        Enemy *boss;
        vector<Enemy*> enemies;
        Map *map;
        CollisionHandler *collisionHandler;
        BorderHandler *borderHandler;
        const float FPS;        
        int width;
        int height;
        bool redraw;
        bool firstOne;

        bool esci;
        bool lastOne;
        bool pressedSpaceBar;
        bool playerCutting(int&, int&);
        void scale();
        void initPos();
        void movePlayer(ALLEGRO_EVENT);
        void moveEnemy(int, bool);
        void printInfo();
    public:
        GameHandler();
        ~GameHandler();
        void Game();
};
#endif