#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H
#include "Map.h"

class CollisionHandler
{
    public:
    bool enemyCollision(bool, const Map*, int, int, bool&, bool&);
    bool playerCollision(const Map*, int, int);

};

#endif