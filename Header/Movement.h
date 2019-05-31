#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Player.h"
#include "CollisionHandler.h"
#include "Map.h"
#include <allegro5/allegro.h>

class Movement
{
    protected:
    CollisionHandler* collisionHandler;

    public:
    Movement();
    ~Movement();
};

#endif