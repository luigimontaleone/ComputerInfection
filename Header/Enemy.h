#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
class Enemy : public Entity
{
    private:
        bool is_boss;
    public:
        Enemy(int x, int y, string path, bool is_boss);
        void moveEnemy();        
};
#endif