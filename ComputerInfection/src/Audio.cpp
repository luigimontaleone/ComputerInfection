#include "../Header/Audio.h"

//costruttore della classe Audio, carica i file .wav dalla cartella Sounds
Audio::Audio()
{
    menu = al_load_sample("../Sounds/menu.wav");
    game = al_load_sample("../Sounds/game.wav");
}

//distruttore della classe Audio
Audio::~Audio()
{
    al_destroy_sample(menu);
    al_destroy_sample(game);

    menu = nullptr;
    game = nullptr;
}

//avvia la traccia del menù, quindi appena si avvia il programma
void Audio::playMenu()
{
    al_play_sample(menu, 0.5, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,&idMenu);
}

//ferma la traccia del menù, quindi appena si avvia il gioco vero e proprio
void Audio::stopMenu()
{
    al_stop_sample(&idMenu);
}

//avvia la traccia subito dopo aver cliccato "play" nel menù
void Audio::playGame()
{
    al_play_sample(game, 0.5, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,&idGame);
}

//ferma la traccia del gioco
void Audio::stopGame()
{
    al_stop_sample(&idGame);
}