#ifndef ENTITY_H
#define ENTITY_H

#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/keyboard.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;

//Rappresenta una Entità generica
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
        ~Entity();
        bool operator==(const Entity&) const;
        int getX() const;
        int getY() const;
        int getSize() const;
        int getSpeed() const;
        void print() const;
        void setX(int X);
        void setY(int Y);
        void setSize(int);
        void setSpeed(int);
};
#endif