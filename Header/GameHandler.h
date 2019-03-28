#include "Player.h"
#include "Enemy.h"
class GameHandler
{
    private:
        //ALLEGRO_DISPLAY_MODE disp_data;
        ALLEGRO_DISPLAY *display;
        ALLEGRO_KEYBOARD_STATE currently;
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
        ALLEGRO_BITMAP *board;
        ALLEGRO_TIMER *timer;
        bool redraw;
        bool comodo = true;
        int logic_map[40][40];
        int rowsMax;
        int rowsMin;
        int colsMax;
        int colsMin;
        int cont = 0;
        const float FPS;

        bool playerCutting(int&, int&);
        void updateRows_Cols();
        void directionPlayer();

    public:
        GameHandler();
        void Game();
        void printBG();
        void printBoard();
        void setCurrentPos(int, int, int);
        void scale();
        void load_map();
        void read_map();
        int read_something_from_map(int, int);
        void movePlayer(ALLEGRO_EVENT);
        void moveEnemy(int, bool);
        bool collision(int, int, bool);
        void min_max(int&, int&, bool);
        void clearMap();
        bool isPointInPath(vector< pair<int,int> >, int, int);
        void floodFill(int,int,int,int);
};