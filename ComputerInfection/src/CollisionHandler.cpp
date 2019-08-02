#include "../Header/CollisionHandler.h"

bool CollisionHandler::enemyCollision(bool is_boss, const Map* map, int x, int y, bool &hit_player, bool &hit_enemy)
{
    int x2 = x;
    int y2 = y;

    //coordinate (non in pixel) degli angoli del nemico
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

    //se uno dei 4 angoli tocca il player che sta tagliando la mappa ritorna false
    if(map->readFromMap(y, x) == -1 || map->readFromMap(y2, x) == -1 || map->readFromMap(y, x2) == -1
    || map->readFromMap(y2, x2) == -1)
    {
        hit_player = true;
        return false;
    }

    //se uno dei 4 angoli tocca il bordo della mappa ritorna false
    if(map->readFromMap(y, x) == 1 || map->readFromMap(y2, x) == 1 || map->readFromMap(y, x2) == 1
    || map->readFromMap(y2, x2) == 1)
    {
        return false;
    }

    //se uno dei 4 angoli tocca un bonus ritorna false
    if(map->readFromMap(y, x) == 5 || map->readFromMap(y2, x) == 5 || map->readFromMap(y, x2) == 5
    || map->readFromMap(y2, x2) == 5)
    { 
        return false;
    }

    //se uno dei 4 angoli tocca la zona già tagliata e non più disponibile ritorna false
    if(map->readFromMap(y, x) == 7 || map->readFromMap(y2, x) == 7 || map->readFromMap(y, x2) == 7
    || map->readFromMap(y2, x2) == 7)
    {
        hit_enemy = true;
        return false;
    }

    return true;
}

bool CollisionHandler::playerCollision(const Map *map, int x, int y) const
{
    //coordinate non in pixel del player
    x = (x - 200) / 15;
    y = y / 15;

    //se il player supera i bordi disponibili ritorna false
    if( x >= map->getMaximumCols() || y >= map->getMaximumRows() || x < 0 || y < 0)
        return false;
    
    
    return (map->readFromMap(y, x) == 1); //ritorna true se il player è sul bordo
}
