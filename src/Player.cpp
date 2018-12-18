#include"../Header/Player.h"
Player::Player(int x_init, int y_init, string path): speed(3), x_init(x_init), y_init(y_init), Entity(x_init, y_init, path, 32)
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
void Player::moveUp()
{
    y -= speed;
}
void Player::moveDown()
{
    y += speed;
}
void Player::moveRight()
{
    x += speed;
}
void Player::moveLeft()
{
    x -= speed;
}
int Player::getSpeed()
{
    return speed;
}