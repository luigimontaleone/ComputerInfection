#ifndef BORDERHANDLER_H
#define BORDERHANDLER_H

#include <vector>
#include "Map.h"

using namespace std;

//classe per la gestione del taglio delle zone interne alla mappa, utilizza l'algoritmo "floodfill"
class BorderHandler
{
    public:
    void floodFill(int,int,int,int,Map*);
    void floodFillControllo(int,int,int,int,bool&,Map*);

};
#endif