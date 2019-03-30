#ifndef BORDERHANDLER_H
#define BORDERHANDLER_H

#include <vector>

using namespace std;

class BorderHandler
{
    public:
        bool isPointInPath(vector< pair<int,int> >, int, int);
        void floodFill(int,int,int,int);
        void floodFillControllo(int,int,int,int,bool&);

};
#endif