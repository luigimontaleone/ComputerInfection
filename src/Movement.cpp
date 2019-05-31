#include "../Header/Movement.h"

Movement::Movement()
{
    collisionHandler = new CollisionHandler();
}

Movement::~Movement()
{
    delete collisionHandler;
}