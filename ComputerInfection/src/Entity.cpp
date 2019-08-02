#include "../Header/Entity.h"

Entity::Entity(int x, int y, string path, int s, int speed): x(x), y(y), size(s), speed(speed)
{
    sprite = al_load_bitmap(path.c_str());
}

Entity::Entity() {}

Entity::~Entity()
{
    al_destroy_bitmap(sprite);
    sprite = nullptr;
}

bool Entity::operator==(const Entity &e) const
{
    if(this->x == e.x && this->y == e.y)
        return true;
    return false;
}

int Entity::getX() const { return x; }
int Entity::getY() const { return y; }
int Entity::getSize() const { return size; }
int Entity::getSpeed() const { return speed; }

void Entity::print() const
{
    al_draw_bitmap(sprite, x, y, 0);
}

void Entity::setX(int X)
{
    x = X;
}

void Entity::setY(int Y)
{
    y = Y;
}

void Entity::setSize(int x)
{
    size = x;
}