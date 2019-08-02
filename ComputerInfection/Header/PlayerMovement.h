#ifndef PLAYERMOVEMENT_H
#define PLAYERMOVEMENT_H

#include "BorderHandler.h"
#include "Movement.h"

/*Gestore dei movimenti del player, eredita da Movement */
class PlayerMovement : public Movement
{
    private:
    BorderHandler* borderHandler;
    
    void cuttingMovement(Player*, Map*, ALLEGRO_EVENT, bool&);
    void changeMapValues(Player*, Map*, bool);

    public:
    PlayerMovement();
    ~PlayerMovement();
    void movement(Player *, Map *, ALLEGRO_EVENT, bool&);

    

};
#endif