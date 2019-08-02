#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "Map.h"
#include "Player.h"

//Classe per la gestione delle collisioni
class CollisionHandler
{
    public:
    bool enemyCollision(bool, const Map*, int, int, bool&, bool&);
    bool playerCollision(const Map*, int, int) const;

};

#endif