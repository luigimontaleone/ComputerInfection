#ifndef MAP_H
#define MAP_H
#include <allegro5/allegro.h>

class Map
{
    private:
        ALLEGRO_BITMAP *background_bw;
        ALLEGRO_BITMAP *background;
        ALLEGRO_BITMAP *board;
        int logic_map[40][40];
        int rowsMax;
        int rowsMin;
        int colsMax;
        int colsMin;
        const int width;
        const int height;
        int cont = 0;
        void updateRows_Cols();
    public:
        void printBG();
        void printBoard();
        void writeOnMap(int, int, int);
        int readFromMap(int, int);
        void clearMap();

};

#endif