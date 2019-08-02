#ifndef AUDIO_H
#define AUDIO_H

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

//Classe per la gestione dell'audio
class Audio
{
    private:
    ALLEGRO_SAMPLE *menu;
    ALLEGRO_SAMPLE *game;
    ALLEGRO_SAMPLE_ID idMenu;
    ALLEGRO_SAMPLE_ID idGame;

    public:
    Audio();
    ~Audio();
    void playMenu();
    void stopMenu();
    void playGame();
    void stopGame();

};
#endif