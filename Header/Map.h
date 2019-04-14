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
        ALLEGRO_BITMAP *border;
        ALLEGRO_BITMAP *saturation;
        int logic_map[40][40];
        int rowsMax;
        int rowsMin;
        int colsMax;
        int colsMin;
        int contSeven;
        int percent;
        int contEnemies;
        const int maximumRows = 40;
        const int maximumCols = 40;
    public:
        Map();
        Map(int, int, int, int, char*, char*);
        ~Map();
        void printBG() const;
        void printBorder() const;
        void printSaturation() const;
        void writeOnMap(int, int, int);
        int readFromMap(int, int) const;
        void clearMap();
        void load_map(string);
        int getRowsMax() const;
        int getRowsMin() const;
        int getColsMax() const;
        int getColsMin() const;
        int getMaximumCols() const;
        int getMaximumRows() const;
        int getContSeven() const;
        int getContEnemies() const;
        void updateRows_Cols();
        int getPercent() const;
        void setContEnemies(int);
        void updatePercent();

};

#endif