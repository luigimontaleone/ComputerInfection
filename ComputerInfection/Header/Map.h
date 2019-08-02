#ifndef MAP_H
#define MAP_H

#include <allegro5/allegro.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*classe rappresentante la mappa sulla quale si sta giocando */
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
        int contEnemies;
        int percent;
        
        const int maximumRows = 40;
        const int maximumCols = 40;

    public:
        Map();
        Map(int, int, int, int, string, string, string);
        ~Map();
        
        //metodi per le stampe
        void printBG() const;
        void printBorder() const;
        void printSaturation() const;

        //metodi per la gestione della mappa logica
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
        int getPercent() const;

        void setContEnemies(int);
        void updateRows_Cols();
        void updatePercent();

};

#endif