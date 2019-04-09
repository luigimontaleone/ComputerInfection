#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "CollisionHandler.h"
//#include "BorderHandler.h"
#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H
class GameHandler
{
    private:
        ALLEGRO_DISPLAY_MODE disp_data;
        ALLEGRO_TRANSFORM trans;
        ALLEGRO_DISPLAY *display;
        ALLEGRO_KEYBOARD_STATE currently;
        Player *player;
        Enemy *boss;
        vector<Enemy*> enemies;
        Map *map;
        CollisionHandler *collisionHandler;
        //BorderHandler *borderHandler;
         int width;
         int height;
        /*int scaleW;
        int scaleH;
        int scaleX;
        int scaleY;*/
        ALLEGRO_TIMER *timer;
        bool redraw;
        bool comodo = true;
        int cont = 0;
        const float FPS;
        bool playerCutting(int&, int&);
        bool lastOne;
    public:
        GameHandler();
        void Game();
        void scale();
        void initPos();
        void movePlayer(ALLEGRO_EVENT);
        void moveEnemy(int, bool);
        bool collision(int, int, bool);
        void floodFill(int,int,int,int);
        void floodFillControllo(int,int,int,int,bool&);
};
#endif