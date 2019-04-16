#ifndef BORDERHANDLER_H
#define BORDERHANDLER_H

#include <vector>
#include "Map.h"

using namespace std;

class BorderHandler
{
    public:
        void floodFill(int,int,int,int,Map*);
        void floodFillControllo(int,int,int,int,bool&,Map*);

};
#endif