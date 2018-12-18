#include "../Header/GameHandler.h"
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
    GameHandler gamehandler;
    gamehandler.Game();
    return 0;
}
