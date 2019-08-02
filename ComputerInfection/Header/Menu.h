#ifndef MENU_H
#define MENU_H

#include <allegro5/allegro.h>
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_primitives.h"
#include <iostream>

using namespace std;

/*Gestore del menu */
class Menu
{
    private:
    ALLEGRO_MOUSE_EVENT eventMouse;
    ALLEGRO_EVENT_QUEUE *menuEventsQueue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_FONT *choicesFont;
    ALLEGRO_FONT *titleFont;
    int menuWidth;
    int menuHeight;
    int sizeTitle;
    int sizeChoices;
    float scaleX;
    float scaleY;
    
    public:
    Menu(int, int, float, float);
    ~Menu();
    int showMenu() const;
    void showCredits() const;

    static const int EXIT = 0;
    static const int PLAY = 1;
    static const int CREDITS = 2;
    
};
#endif