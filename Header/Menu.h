#ifndef MENU_H
#define MENU_H

#include <allegro5/allegro.h>
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include <iostream>

using namespace std;

class Menu
{
    private:
    ALLEGRO_DISPLAY *menuDisplay;
    ALLEGRO_DISPLAY_MODE disp_data;
    ALLEGRO_TRANSFORM trans;
    ALLEGRO_MOUSE_EVENT eventMouse;
    ALLEGRO_EVENT_QUEUE *menuEventsQueue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_FONT *choicesFont;
    ALLEGRO_FONT *titleFont;
    int menuWidth;
    int menuHeight;
    int sizeTitle;
    int sizeChoices;

    public:
    Menu();
    ~Menu();
    int showMenu() const;
    void initDisplay();
    void closeDisplay();

    static const int EXIT = 0;
    static const int PLAY = 1;
    static const int CREDITS = 2;
};
#endif