#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <string>
using namespace std;
class Player
{
    private:
        int x;
        int y;
        int x_init;
        int y_init;
        int lives;
        int score;
        ALLEGRO_BITMAP *sprite;
        
    public:
        Player(int x_init, int y_init, string path);
};