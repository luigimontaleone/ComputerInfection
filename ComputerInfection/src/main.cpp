#include "../Header/GameHandler.h"
#include "../Header/Menu.h"
#include "../Header/Audio.h"
#include <iostream>

void initDisplay(ALLEGRO_DISPLAY *, int &, int &, float&, float&);

int main()
{
    srand(time(NULL));

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
    ALLEGRO_DISPLAY *display;
    int displayW, displayH;
    float scaleX, scaleY;
    initDisplay(display, displayW, displayH, scaleX, scaleY);
    Audio *audio = new Audio();
    Menu *menu = new Menu(displayW, displayH, scaleX, scaleY);
    audio->playMenu();
    int choice = menu->showMenu();
    while(choice != Menu::EXIT)
    {
        switch (choice)
        {
            case Menu::PLAY :
            {
                delete menu;
                audio->stopMenu();
                audio->playGame();
                GameHandler *gamehandler = new GameHandler(displayW, displayH);
                gamehandler->Game();
                delete gamehandler;
                audio->stopGame();
                audio->playMenu();
                menu = new Menu(displayW, displayH, scaleX, scaleY);
                break;
            }
            case Menu::CREDITS :
            {
                menu->showCredits();
                break;
            }
        
            default:
                break;
        }
        choice = menu->showMenu();
    }
    delete menu;
    delete audio;
    return 0;
}


void initDisplay(ALLEGRO_DISPLAY *display, int &displayW, int &displayH, float &scaleX, float &scaleY)
{
    ALLEGRO_DISPLAY_MODE disp_data;
    ALLEGRO_TRANSFORM trans;
    al_get_display_mode(al_get_num_display_modes()-1, &disp_data);
    int width = disp_data.width;
    int height = disp_data.height;
    displayW = 800;
    displayH = 600;
    scaleX = (width / (float) displayW);
    scaleY = (height / (float) displayH);
    display = al_create_display(width, height);
    if(!display)
    {
        cout<<"failed to create menu display";
        return;
    }
    al_identity_transform(&trans);
    al_scale_transform(&trans, scaleX, scaleY);
    al_use_transform(&trans);
}