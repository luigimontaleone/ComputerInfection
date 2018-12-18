#include"../Header/Player.h"
Player::Player(int x_init, int y_init, string path): speed(3), x_init(x_init), y_init(y_init), Entity(x_init, y_init, path,32)
{
    lives = 3;
    score = 0;
}
void Player::setXinit(int X)
{
    x_init = X;
}
int Player::getXinit()
{
    return x_init;
}
void Player::setYinit(int Y)
{
    y_init = Y;
}
int Player::getYinit()
{
    return y_init;
}
int Player::getLives()
{
    return lives;
}
int Player::getScore()
{
    return score;
}
void Player::decreaseLives()
{
    lives--;
}
void Player::increaseScore()
{
    score += 100;
}
void Player::movePlayer(ALLEGRO_EVENT ev)
{
    switch(ev.keyboard.keycode)
    {
        case ALLEGRO_KEY_UP:
            moveUp();
            break;
        case ALLEGRO_KEY_DOWN:
            moveDown();
            break;
        case ALLEGRO_KEY_RIGHT:
            moveRight();
            break;
        case ALLEGRO_KEY_LEFT:
            moveLeft();
            break;
        case ALLEGRO_KEY_SPACE:
            break;
    }
    print();
}
void Player::moveUp()
{
    if(!collisionPlayer(x,y-speed))
        y -= speed;
}
void Player::moveDown()
{
    if(!collisionPlayer(x,y+speed))
        y += speed;
}
void Player::moveRight()
{
    if(!collisionPlayer(x+speed,y))
        x += speed;
}
void Player::moveLeft()
{
    if(!collisionPlayer(x-speed,y))
        x -= speed;
}
bool Player::collisionPlayer(int tempX, int tempY)
{
    if( tempX<0 || tempX>(800-size) || tempY<0 || tempY>(600-size) )
        return true;
    return false;
}