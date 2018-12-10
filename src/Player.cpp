#include"../Header/Player.h"
Player::Player(int x_init, int y_init, string path): x_init(x_init), y_init(y_init), x(x_init), y(y_init)
{
    lives = 3;
    score = 0;
    sprite = al_load_bitmap(path.c_str());
}