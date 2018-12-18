#include "Player.h"
#include "Enemy.h"
class GameHandler
{
    private:
        //ALLEGRO_DISPLAY_MODE disp_data;
        ALLEGRO_DISPLAY *display;
        Player *player;
        Enemy *boss;
        Enemy **enemies;
        const int width;
        const int height;
        /*int scaleW;
        int scaleH;
        int scaleX;
        int scaleY;*/
        ALLEGRO_BITMAP *background_bw;
        ALLEGRO_BITMAP *background;
        ALLEGRO_TIMER *timer;
        bool redraw;
        const float FPS;

    public:
        GameHandler();
        void Game();
        void printBG();
        void scale();
};