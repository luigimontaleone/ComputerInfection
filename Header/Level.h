#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <list>
#include <dirent.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include <iostream>

using namespace std;

class Level
{
    private:
    list<string> levels;
    int numLevel;
    int screenWidth;
    int screenHeight;
    ALLEGRO_FONT *font;
    void setLevels();

    public:
    Level(ALLEGRO_FONT*,int,int);
    string front() const;
    void pop_front();
    bool empty() const;
    void newLevel();

};

#endif