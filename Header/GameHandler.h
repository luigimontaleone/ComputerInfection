#include "Player.h"
#include "Enemy.h"
class GameHandler
{
    private:
        //ALLEGRO_DISPLAY_MODE disp_data;
        ALLEGRO_DISPLAY *display;
        Player *player;
        Enemy *boss;
        vector<Enemy*> enemies;
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
        int logic_map[40][40];
        int rows;
        int cols;
        const float FPS;

    public:
        GameHandler();
        void Game();
        void printBG();
        void scale();
        void load_map();
        void read_map();
        int read_something_from_map(int, int);
        void movePlayer(ALLEGRO_EVENT);
        void moveEnemy(int, bool);
        bool collision(int, int, bool);
};