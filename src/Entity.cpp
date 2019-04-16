#include "../Header/Entity.h"
Entity::Entity(int x, int y, string path, int s, int speed): x(x), y(y), size(s), speed(speed)
{
    sprite = al_load_bitmap(path.c_str());
}
Entity::Entity() {}
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
void Entity::print()
{
    al_draw_bitmap(sprite, x, y, 0);
}
int Entity::getSize()
{
    return size;
}
void Entity::setSize(int x)
{
    size = x;
}
int Entity::getSpeed()
{
    return speed;
}
Entity::~Entity()
{
    al_destroy_bitmap(sprite);
    sprite = nullptr;
}