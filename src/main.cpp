#include "../Header/GameHandler.h"
#include "../Header/Menu.h"
#include <iostream>
int main()
{
    if(!al_init())
    {
        cerr << "failed to initialize allegro";
        return -1;
    }
    if(!al_init_image_addon())
    {
        cout<<"failed image addon";
        return -1;
    }
    if(!al_init_primitives_addon())
    {
        cout<<"failed primitives addon";
        return -1;
    }
    if(!al_install_keyboard())
    {
        cout<<"failed install keyboard";
        return -1;
    }
    if(!al_init_font_addon())
    {
        cerr<<"failed to install font addon";
        return 1;
    }
    if(!al_init_ttf_addon())
    {
        cerr<<"failed to install ttf addon";
        return 1;
    }
    Menu *menu = new Menu();
    int choice = menu->showMenu();
    while(choice != Menu::EXIT)
    {
        menu->closeDisplay();
        switch (choice)
        {
            case Menu::PLAY :
            {
                GameHandler *gamehandler = new GameHandler();
                gamehandler->Game();
                delete gamehandler;
                break;
            }
            case Menu::CREDITS :
            {
                break;
            }
        
            default:
                break;
        }
        menu->initDisplay();
        choice = menu->showMenu();
    }
    delete menu;
    return 0;
}
