#ifndef ENTITY_H
#define ENTITY_H

#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;

class Entity
{
    protected:
        int x;
        int y;
        int size;
        int speed;
        ALLEGRO_BITMAP *sprite;

    public:
        Entity(int x, int y, string path, int size, int speed);
        Entity();
        void setX(int X);
        int getX();
        void setY(int Y);
        int getY();
        void print();
        int getSize();
        void setSize(int);
        int getSpeed();
        void setSpeed(int);
};
#endif