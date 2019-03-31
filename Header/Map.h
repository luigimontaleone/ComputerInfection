#ifndef MAP_H
#define MAP_H
#include <allegro5/allegro.h>
#include <iostream>
#include <string>
#include <fstream>


using namespace std;

class Map
{
    private:
        ALLEGRO_BITMAP *background_bw;
        ALLEGRO_BITMAP *background;
        ALLEGRO_BITMAP *border;
        int logic_map[40][40];
        int rowsMax;
        int rowsMin;
        int colsMax;
        int colsMin;
    public:
        Map();
        Map(int, int, int, int, char*, char*, char*);
        ~Map();
        void printBG();
        void printBorder();
        void writeOnMap(int, int, int);
        int readFromMap(int, int);
        void clearMap();
        void load_map(string);
        //void read_map();
        int getRowsMax();
        int getRowsMin();
        int getColsMax();
        int getColsMin();
        void updateRows_Cols();

};

#endif