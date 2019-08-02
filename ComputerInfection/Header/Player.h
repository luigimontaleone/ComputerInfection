#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

/*Rappresenta il Player, eredita da Entity */
class Player : public Entity
{
    private:
    vector<int> passiX;
    vector<int> passiY;
    int lives;
    int score;
    int posUpDown;
    int posLeftRight;
    bool cutting;
    bool comingBack;

    public:
    Player(int x, int y, string path);

    //metodi per la gestione dei passi di un "taglio"
    void aggiungiPassiX(int);
    void aggiungiPassiY(int);
    const vector<int>& getPassiX() const;
    const vector<int>& getPassiY() const;
    void popBackPassi();
    void svuotaPassi();

    int getLives() const;
    int getScore() const;
    bool getCutting() const;
    bool getComingBack() const;
    void setComingBack(bool);
    void setCutting(bool);
    void setScore(int);
    
    void decreaseLives();
    void increaseScore(); 

    //metodi per i movimenti 
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
        
};
#endif