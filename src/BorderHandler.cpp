#include "../Header/BorderHandler.h"

void BorderHandler::floodFill(int x, int y, int fill_color, int boundary_color, Map* map)
{
    if(map->readFromMap(x,y) != fill_color && map->readFromMap(x,y) != boundary_color)
    {
        map->writeOnMap(x, y, fill_color);
        if(x + 1 < map->getRowsMax())
            floodFill(x+1,y,fill_color,boundary_color, map);
        if(y + 1 < map->getColsMax())
            floodFill(x,y+1,fill_color,boundary_color, map);
        if(x - 1 >= map->getRowsMin())
            floodFill(x-1,y,fill_color,boundary_color, map);
        if(y - 1 >= map->getColsMin())
            floodFill(x,y-1,fill_color,boundary_color, map);
    }
}
void BorderHandler::floodFillControllo(int x,int y,int fill_color,int boundary_color, bool &controllo, Map* map)
{
    if(map->readFromMap(x,y) != 4 && map->readFromMap(x,y) != 1 && map->readFromMap(x,y) != boundary_color && controllo
     && map->readFromMap(x,y) != fill_color)
    {
        if(map->readFromMap(x,y) == 3)
        {
            controllo = false;
            return;
        }
        map->writeOnMap(x, y, fill_color);
        if(x + 1 < map->getRowsMax())
            floodFillControllo(x+1,y,fill_color,boundary_color, controllo, map);
        if(y + 1 < map->getColsMax())
            floodFillControllo(x,y+1,fill_color,boundary_color, controllo, map);
        if(x - 1 >= map->getRowsMin())
            floodFillControllo(x-1,y,fill_color,boundary_color, controllo, map);
        if(y - 1 >= map->getColsMin())
            floodFillControllo(x,y-1,fill_color,boundary_color, controllo, map);
    }
}