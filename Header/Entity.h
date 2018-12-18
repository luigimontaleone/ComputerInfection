#ifndef ENTITY_H
#define ENTITY_H

#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include <string>
#include <iostream>

using namespace std;

class Entity
{
    private:
        int x;
        int y;
        ALLEGRO_BITMAP *sprite;

    public:
        Entity(int x, int y, string path);
        void setX(int X);
        int getX();
        void setY(int Y);
        int getY();
};
#endif