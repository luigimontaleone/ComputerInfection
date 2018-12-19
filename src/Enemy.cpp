#include"../Header/Enemy.h"
Enemy::Enemy(int x, int y, string path, bool is_boss, int speed): Entity(x, y, path, 32, speed)
{
    this->is_boss = is_boss;
    if(is_boss)
    {
        size = 64;
        dir = rand()%8 + 1;
    }
}
void Enemy::move()
{
    switch(dir)
    {
        case 1: //est
            x += speed;
            break;
        case 2: //sud-est
            x += speed;
            y += speed;
            break;
        case 3: //sud
            y += speed;
            break;
        case 4: //sud-ovest
            x -= speed;
            y += speed;
            break;
        case 5: //ovest
            x -= speed;
            break;
        case 6: //nord-ovest
            x -= speed;
            y -= speed;
            break;
        case 7: //nord
            y -= speed;
            break;
        case 8: //nord-est
            x += speed;
            y -= speed;
            break;
        default:
            break;
    }
    print();
}
void Enemy::set_dir(int dir)
{
    this->dir = dir;
}