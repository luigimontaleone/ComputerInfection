#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
class Player : public Entity
{
    private:
        vector<int> passiX;
        vector<int> passiY;
        int lives;
        int score;
        bool cutting;
        bool left;

        
    public:
        Player(int x, int y, string path);
        void aggiungiPassiX(int);
        void aggiungiPassiY(int);
        const vector<int>& getPassiX();
        const vector<int>& getPassiY();
        void svuotaPassi();
        int getSizePassi();
        int getLives();
        int getScore();
        bool getCutting();
        void setCutting(bool);
        void decreaseLives();
        void increaseScore();  
        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();
        bool getLeft();
        void setLeft(bool);
};
#endif