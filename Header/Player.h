#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
class Player : public Entity
{
    private:
        int x_init;
        int y_init;
        int lives;
        int score;
        const int speed;
        
    public:
        Player(int x_init, int y_init, string path);
        void setXinit(int X);
        int getXinit();
        void setYinit(int Y);
        int getYinit();
        int getLives();
        int getScore();
        void decreaseLives();
        void increaseScore();  
        void movePlayer(ALLEGRO_EVENT);
        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();
        bool collisionPlayer(int,int);
};
#endif