#include "../Header/CollisionHandler.h"

bool CollisionHandler::enemyCollision(bool is_boss, const Map* map, int x, int y, bool &hit_player, bool &hit_enemy)
{
    int x2 = x;
    int y2 = y;
    if(is_boss)
    {
        x = (x - 200 - 16) / 15;
        y = (y - 16) / 15;
        x2 = (x2 - 200 + 64) / 15;
        y2 = (y2 + 64) / 15;
    }
    else
    {
        x = (x - 200 - 8) / 15;
        y = (y - 8) / 15;
        x2 = (x2 - 200 + 32) / 15;
        y2 = (y2 + 32) / 15;
    }

    if(map->readFromMap(y, x) == -1 || map->readFromMap(y2, x) == -1 || map->readFromMap(y, x2) == -1
    || map->readFromMap(y2, x2) == -1)
    {
        hit_player = true;
        return false;
    }
    if(map->readFromMap(y, x) == 1 || map->readFromMap(y2, x) == 1 || map->readFromMap(y, x2) == 1
    || map->readFromMap(y2, x2) == 1)
    { 
        return false;
    }
    if(map->readFromMap(y, x) == 7 || map->readFromMap(y2, x) == 7 || map->readFromMap(y, x2) == 7
    || map->readFromMap(y2, x2) == 7)
    {
        hit_enemy = true;
        return false;
    }      
    return true;
}

bool CollisionHandler::playerCollision(const Map *map, int x, int y)
{
    x = (x - 200) / 15;
    y = y / 15;
    if( x >= map->getMaximumCols() || y >= map->getMaximumRows() || x < 0 || y < 0)
        return false;
    int something = map->readFromMap(y, x);
    return !((something != 1));
}
