#include "../Header/Entity.h"
Entity::Entity(int x, int y, string path): x(x), y(y)
{
    sprite = al_load_bitmap(path.c_str());
}
void Entity::setX(int X)
{
    x = X;
}
int Entity::getX()
{
    return x;
}
void Entity::setY(int Y)
{
    y = Y;
}
int Entity::getY()
{
    return y;
}
