#include "../Header/Audio.h"

Audio::Audio()
{
    menu = al_load_sample("../Sounds/menu.wav");
    game = al_load_sample("../Sounds/game.wav");
}

Audio::~Audio()
{
    al_destroy_sample(menu);
    al_destroy_sample(game);
    menu = nullptr;
    game = nullptr;
}

void Audio::playMenu()
{
    al_play_sample(menu, 0.5, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,&idMenu);
}

void Audio::stopMenu()
{
    al_stop_sample(&idMenu);
}

void Audio::playGame()
{
    al_play_sample(game, 0.5, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,&idGame);
}

void Audio::stopGame()
{
    al_stop_sample(&idGame);
}