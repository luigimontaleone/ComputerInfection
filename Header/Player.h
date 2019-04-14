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
        int posUpDown;
        int posLeftRight;
        bool comingBack;
    public:
        Player(int x, int y, string path);
        void aggiungiPassiX(int);
        void aggiungiPassiY(int);
        const vector<int>& getPassiX();
        const vector<int>& getPassiY();
        void popBackPassi();
        void svuotaPassi();
        int getLives();
        int getScore();
        bool getCutting();
        bool getComingBack();
        void setComingBack(bool);
        void setCutting(bool);
        void setScore(int);
        void decreaseLives();
        void increaseScore();  
        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();
        
};
#endif