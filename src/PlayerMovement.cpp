#include "../Header/PlayerMovement.h"

PlayerMovement::PlayerMovement()
{
    borderHandler = new BorderHandler();
}

PlayerMovement::~PlayerMovement()
{
    delete borderHandler;
}

void PlayerMovement::movement(Player* player, Map* map, ALLEGRO_EVENT ev, bool &pressedSpaceBar)
{
    if(player->getCutting())
    {
        cuttingMovement(player, map, ev, pressedSpaceBar);
    }
    else
    {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_UP:
                    if(collisionHandler->playerCollision(map,player->getX(),player->getY() - player->getSpeed()))//collision(player->getX(), player->getY() - player->getSpeed(), true))
                        player->moveUp();
                    break;
                case ALLEGRO_KEY_DOWN:
                    if(collisionHandler->playerCollision(map,player->getX(),player->getY() + player->getSpeed()))//collision(player->getX(), player->getY() + player->getSpeed(), true))
                        player->moveDown();
                    break;
                case ALLEGRO_KEY_RIGHT:
                    if(collisionHandler->playerCollision(map,player->getX() + player->getSpeed(),player->getY()))//collision(player->getX() + player->getSpeed(), player->getY(), true))
                        player->moveRight();
                    break;
                case ALLEGRO_KEY_LEFT:
                    if(collisionHandler->playerCollision(map,player->getX() - player->getSpeed(),player->getY()))//collision(player->getX() - player->getSpeed(), player->getY(), true))
                        player->moveLeft();
                    break;
                default:
                    break;
            }        
    }
}

void PlayerMovement::cuttingMovement(Player* player, Map* map, ALLEGRO_EVENT ev, bool &pressedSpaceBar)
{
    bool sostituisci = false;
    bool borderCutting = false;
    int xBefore = player->getX();
    int yBefore = player->getY();
    int valBefore = map->readFromMap((player->getY()) / 15, (player->getX() - 200) / 15);
    switch(ev.keyboard.keycode)
    {                           
        case ALLEGRO_KEY_UP:
            player->moveUp();
            break;
        case ALLEGRO_KEY_DOWN:
            player->moveDown();
            break;
        case ALLEGRO_KEY_LEFT:
            player->moveLeft();
            break;
        case ALLEGRO_KEY_RIGHT:
            player->moveRight();
            break;
        default:
            break;
    }
    int xAfter = (player->getX()-200) /15;
    int yAfter = player->getY() / 15;
    if(xAfter > map->getColsMax()-1 || yAfter > map->getRowsMax()-1 || 
    xAfter < map->getColsMin() || yAfter < map->getRowsMin() 
    || map->readFromMap(yAfter, xAfter) == 7 ||
        map->readFromMap(yAfter, xAfter) == -1)
    {
        player->setX(xBefore);
        player->setY(yBefore);
        //cout<<"error"<<endl;
        return;
    }
    if(map->readFromMap(yAfter, xAfter) == 1)  
    {
        if(player->getPassiX().size() < 2)
            borderCutting = true;
        map->writeOnMap(yAfter, xAfter, -1);
        sostituisci = true;
    }
    map->writeOnMap(yBefore / 15, (xBefore - 200) / 15, -1);
    player->aggiungiPassiX((xBefore - 200) / 15);
    player->aggiungiPassiY(yBefore / 15);
    map->printBorder();     
    
    if(sostituisci)
    {
        pressedSpaceBar = false;
        this->changeMapValues(player, map, borderCutting);
    }
        
}

void PlayerMovement::changeMapValues(Player* player, Map* map, bool borderCutting)
{
    player->aggiungiPassiX((player->getX() - 200) / 15);
    player->aggiungiPassiY((player->getY()) / 15);
    if(!borderCutting)
    {
        int medioY = 0;
        int medioX = 0;
        for(int i = map->getRowsMin(); i < map->getRowsMax(); i++)
        {
            bool found = false;
            for(int j = map->getColsMin(); j < map->getColsMax(); j++)
            {
                
                bool uguale = false;
                for(int p = 0; p < player->getPassiY().size(); p++)
                {
                    if(player->getPassiY()[p] == i && player->getPassiX()[p] == j)
                    {
                        uguale = true;
                        break;
                    }
                }
                if(!uguale && map->readFromMap(i, j) != 7 && map->readFromMap(i, j) != 1 && !found
                && map->readFromMap(i, j) != 4)
                { 
                    bool ctrl = true;
                    borderHandler->floodFillControllo(i, j, -2, -1, ctrl, map);
                    map->clearMap();
                    if(ctrl)
                    {
                        medioX = j;
                        medioY = i;
                        found = true;
                    }
                }                    
            }
            if(found)
                break;
        }
        borderHandler->floodFill(medioY, medioX, 7, -1, map); 
        for(int i = map->getRowsMin(); i < map->getRowsMax(); i++)
        {
            for(int j = map->getColsMin(); j < map->getColsMax(); j++)
            {
                if(map->readFromMap(i, j) == -1)
                    map->writeOnMap(i, j, 1);
            }
        }
        player->svuotaPassi();
        
    }
    else
    {
        while(player->getPassiX().size() > 0)
        {
            int x_tmp = player->getPassiX()[player->getPassiX().size() - 1 ];
            int y_tmp = player->getPassiY()[player->getPassiY().size() - 1 ];
            map->writeOnMap(y_tmp, x_tmp, 1);
            player->popBackPassi();
        }
    }
    map->updateRows_Cols();
    map->updatePercent();
}