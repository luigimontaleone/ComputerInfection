#include"../Header/Player.h"
//costruttore della classe Player che setta tutte le variabili
Player::Player(int x, int y, string path):Entity(x, y, path, 32, 15)
{
    lives = 3;
    score = 0;
    cutting = false;
    comingBack = false;
}
//metodi per aggiungere la coordinata x e y al vettore dei passi(solo quando sta tagliando la mappa)
void Player::aggiungiPassiX(int x)
{
    passiX.push_back(x);
}
void Player::aggiungiPassiY(int x)
{
    passiY.push_back(x);
}

const vector<int>& Player::getPassiX() const { return passiX; }
const vector<int>& Player::getPassiY() const { return passiY; }

void Player::svuotaPassi()
{
    passiX.clear();
    passiY.clear();
}
void Player::popBackPassi()
{
    if(!passiX.empty())
    {
        passiX.pop_back();
        passiY.pop_back();
    }
}

int Player::getLives() const { return lives; }
int Player::getScore() const { return score; }
bool Player::getCutting() const { return cutting; }
bool Player::getComingBack() const { return comingBack; }

void Player::setComingBack(bool cb)
{
    comingBack = cb;
}

void Player::setScore(int sc)
{
    score = sc;
}

//setta la variabile cutting a true se sta tagliando, false altrimenti
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

//metodi per far muovere il player, aggiungendo alla coordinata attuale la velocità

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