#include "../Header/EnemyMovement.h"

void EnemyMovement::movement(Enemy * enemy, Player* player, Map *map, bool &pressedSpaceBar)
{
    bool collisione = false;
    int dir = enemy->get_dir();
    bool hit_player = false;
    bool hit_enemy = false;
    switch (dir)
    {
        case 1:
            if(!collisionHandler->enemyCollision(enemy->getIsBoss(), map, enemy->getX() + enemy->getSpeed(), enemy->getY(), hit_player, hit_enemy))
            {
                collisione = true;
            }
            break;
        case 2:
            if(!collisionHandler->enemyCollision(enemy->getIsBoss(), map, enemy->getX() + enemy->getSpeed(), enemy->getY() + enemy->getSpeed(), hit_player, hit_enemy))
            {
                collisione = true;
            }            
            break;
        case 3:
            if(!collisionHandler->enemyCollision(enemy->getIsBoss(), map, enemy->getX(), enemy->getY() + enemy->getSpeed(), hit_player, hit_enemy))
            {
                collisione = true;
            }
            break;
        case 4:
            if(!collisionHandler->enemyCollision(enemy->getIsBoss(), map, enemy->getX() - enemy->getSpeed(), enemy->getY() + enemy->getSpeed(), hit_player, hit_enemy))
            {
                collisione = true;
            }
            break;
        case 5:
            if(!collisionHandler->enemyCollision(enemy->getIsBoss(), map, enemy->getX() - enemy->getSpeed(), enemy->getY(), hit_player, hit_enemy))
            {
                collisione = true;
            }
            break;
        case 6:
            if(!collisionHandler->enemyCollision(enemy->getIsBoss(), map, enemy->getX() - enemy->getSpeed(), enemy->getY() - enemy->getSpeed(), hit_player, hit_enemy))
            {
                collisione = true;
            }
            break;
        case 7:
            if(!collisionHandler->enemyCollision(enemy->getIsBoss(), map, enemy->getX(), enemy->getY() - enemy->getSpeed(), hit_player, hit_enemy))
            {
                collisione = true;
            }
            break;
        case 8:
            if(!collisionHandler->enemyCollision(enemy->getIsBoss(), map, enemy->getX() + enemy->getSpeed(), enemy->getY() - enemy->getSpeed(), hit_player, hit_enemy))
            {
                collisione = true;
            }
            break;
        default:
            break;
    }
    if(hit_enemy)
    {
        cout<<"PRIMA"<<endl;
            for(int i = 0; i < map->getMaximumRows(); i++)
            {
                for(int j = 0; j < map->getMaximumCols(); j++)
                {
                    cout<<map->readFromMap(i,j);
                }
                cout<<endl;
            }
            cout<<endl;
        enemy->die();
        map->writeOnMap(enemy->getY() / 15, (enemy->getX() - 200)/ 15, 7);
        cout<<"DOPO"<<endl;
            for(int i = 0; i < map->getMaximumRows(); i++)
            {
                for(int j = 0; j < map->getMaximumCols(); j++)
                {
                    cout<<map->readFromMap(i,j);
                }
                cout<<endl;
            }
            cout<<endl<<endl;
    }
    else if(hit_player)
    {
        pressedSpaceBar = false;
        collisionWithPlayer(player, map);
    }
    
    else if(collisione && (enemy->getAlive() || enemy->getIsBoss()))
    {
        newPosition(enemy, map);
    }
    if(enemy->getAlive())
    {
        map->writeOnMap(enemy->getY() / 15, (enemy->getX() - 200)/ 15, 0);
        enemy->move();
        if(enemy->getIsBoss())
            map->writeOnMap(enemy->getY() / 15, (enemy->getX() - 200)/ 15, 3);
        else
            map->writeOnMap(enemy->getY() / 15, (enemy->getX() - 200)/ 15, 4);
    }
}

void EnemyMovement::newPosition(Enemy * enemy, Map* map)
{
    bool trovato = false;
    bool hit_player = false;//inutili questi
    bool hit_enemy = false;//booleani
    int new_dir = 0;
    while (!trovato)
    {
        if(map->readFromMap(enemy->getY()/15, (enemy->getX()-200)/15) == 7)//se l'enemy è nel while per trovare una nuova direzione
            return;                                                        //ma il player poco prima ha tagliato una zona e l'enemy non si è ancora "accorto" di essere morto
        new_dir = (rand() % 8) + 1;
        switch (new_dir)
        {
            
            case 1:
                if(collisionHandler->enemyCollision(enemy->getIsBoss(), map, enemy->getX() + enemy->getSpeed(), enemy->getY(), hit_player, hit_enemy))
                {
                    trovato = true;
                }
                break;
            case 2:
                if(collisionHandler->enemyCollision(enemy->getIsBoss(), map, enemy->getX() + enemy->getSpeed(), enemy->getY() + enemy->getSpeed(), hit_player, hit_enemy))
                {
                    trovato = true;
                }
                break;
            case 3:
                if(collisionHandler->enemyCollision(enemy->getIsBoss(), map, enemy->getX() + enemy->getSpeed(), enemy->getY() + enemy->getSpeed(), hit_player, hit_enemy))
                {
                    trovato = true;
                }
                break;
            case 4:
                if(collisionHandler->enemyCollision(enemy->getIsBoss(), map, enemy->getX() - enemy->getSpeed(), enemy->getY() + enemy->getSpeed(), hit_player, hit_enemy))
                {
                    trovato = true;
                }
                break;
            case 5:
                if(collisionHandler->enemyCollision(enemy->getIsBoss(), map, enemy->getX() - enemy->getSpeed(), enemy->getY(), hit_player, hit_enemy))
                {
                    trovato = true;
                }
                break;
            case 6:
                if(collisionHandler->enemyCollision(enemy->getIsBoss(), map, enemy->getX() - enemy->getSpeed(), enemy->getY() - enemy->getSpeed(), hit_player, hit_enemy))
                {
                    trovato = true;
                }
                break;
            case 7:
                if(collisionHandler->enemyCollision(enemy->getIsBoss(), map, enemy->getX(), enemy->getY() - enemy->getSpeed(), hit_player, hit_enemy))
                {
                    trovato = true;
                }
                break;
            case 8:
                if(collisionHandler->enemyCollision(enemy->getIsBoss(), map, enemy->getX() + enemy->getSpeed(), enemy->getY() - enemy->getSpeed(), hit_player, hit_enemy))
                {
                    trovato = true;
                }
                break;
            default:
                break;
        }
    }
    enemy->set_dir(new_dir);
}

void EnemyMovement::collisionWithPlayer(Player* player, Map* map)
{
    player->decreaseLives();
    if(player->getLives() <= 0)
        return;
    player->aggiungiPassiX((player->getX() - 200) / 15);
    player->aggiungiPassiY((player->getY()) / 15);
    int x_tmp = player->getPassiX()[0];
    int y_tmp = player->getPassiY()[0];
    player->setX((x_tmp * 15) + 200);
    player->setY(y_tmp * 15);
    while(player->getPassiX().size() > 0)
    {
        x_tmp = player->getPassiX()[player->getPassiX().size() - 1 ];
        y_tmp = player->getPassiY()[player->getPassiY().size() - 1 ];
        if(player->getPassiX().size() > 1)
            map->writeOnMap(y_tmp, x_tmp, 0);
        else
            map->writeOnMap(y_tmp, x_tmp, 1);
        player->popBackPassi();
    }
}