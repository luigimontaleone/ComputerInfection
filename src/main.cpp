#include "../Header/GameHandler.h"
#include "../Header/Menu.h"
#include "../Header/Audio.h"
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
    if(!al_install_audio())
    {
      cerr<<"failed to initialize audio!\n";
      return -1;
    }

    if(!al_init_acodec_addon())
    {
      cerr<<"failed to initialize audio codecs!\n";
      return -1;
    }
	
    if (!al_reserve_samples(1))
    {
      cerr<<"failed to reserve samples!\n";
      return -1;
    }

    Audio *audio = new Audio();
    Menu *menu = new Menu();
    audio->playMenu();
    int choice = menu->showMenu();
    while(choice != Menu::EXIT)
    {
        delete menu;
        switch (choice)
        {
            case Menu::PLAY :
            {
                audio->stopMenu();
                audio->playGame();
                GameHandler *gamehandler = new GameHandler();
                gamehandler->Game();
                delete gamehandler;
                audio->stopGame();
                break;
            }
            case Menu::CREDITS :
            {
                break;
            }
        
            default:
                break;
        }
        audio->playMenu();
        menu = new Menu();
        choice = menu->showMenu();
    }
    delete menu;
    delete audio;
    return 0;
}
