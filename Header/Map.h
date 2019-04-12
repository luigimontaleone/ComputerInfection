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
        ALLEGRO_BITMAP *saturation;
        int logic_map[40][40];
        int rowsMax;
        int rowsMin;
        int colsMax;
        int colsMin;
        double percent;
        const int maximumRows = 40;
        const int maximumCols = 40;
    public:
        Map();
        Map(int, int, int, int, char*, char*, char*);
        ~Map();
        void printBG() const;
        void printBorder() const;
        void writeOnMap(int, int, int);
        int readFromMap(int, int) const;
        void clearMap();
        void load_map(string);
        //void read_map();
        int getRowsMax() const;
        int getRowsMin() const;
        int getColsMax() const;
        int getColsMin() const;
        int getMaximumCols() const;
        int getMaximumRows() const;
        void updateRows_Cols();
        float getPercent() const;
        void updatePercent();

};

#endif