#include"../Header/Player.h"
Player::Player(int x, int y, string path):Entity(x, y, path, 32, 15)
{
    lives = 3;
    score = 0;
    cutting = false;
}

void Player::aggiungiPassiX(int x)
{
    passiX.push_back(x);
}
void Player::aggiungiPassiY(int x)
{
    passiY.push_back(x);
}
const vector<int>& Player::getPassiX()
{
    return passiX;
}
const vector<int>& Player::getPassiY()
{
    return passiY;
}
void Player::svuotaPassi()
{
    passiX.clear();
    passiY.clear();
}
int Player::getSizePassi()
{
    return passiX.size();
}
int Player::getLives()
{
    return lives;
}
int Player::getScore()
{
    return score;
}
bool Player::getCutting()
{
    return cutting;
}
void Player::setCutting(bool cut)
{
    cutting = cut;
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