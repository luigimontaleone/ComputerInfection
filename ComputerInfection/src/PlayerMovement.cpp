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
    if(player->getCutting()) //se il player è nella "modalità taglio" c'è il metodo apposito "cuttingMovement"
    {
        cuttingMovement(player, map, ev, pressedSpaceBar);
    }
    else //se è un movimento "normale"
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
            return;
    }

    int xAfter = (player->getX() - 200) / 15;
    int yAfter = player->getY() / 15;
    

    if(xAfter > map->getColsMax() - 1 || yAfter > map->getRowsMax() - 1 || xAfter < map->getColsMin()
    || yAfter < map->getRowsMin()  || map->readFromMap(yAfter, xAfter) == 7
    || map->readFromMap(yAfter, xAfter) == -1)  //se il player, facendo il movimento, è andato fuori mappa
    {                                           //oppure ha incontrato degli ostacoli
            
        player->setX(xBefore);
        player->setY(yBefore);
        return;
    }

    if(map->readFromMap(yAfter, xAfter) == 1)//se il player ha completato il taglio  
    {
        if(player->getPassiX().size() < 2) //se i passi fatti sono meno di 2 vuol dire che il player
            borderCutting = true;   //sta tagliando lungo il bordo
        
        map->writeOnMap(yAfter, xAfter, -1);
        sostituisci = true;
    }

    map->writeOnMap(yBefore / 15, (xBefore - 200) / 15, -1);
    player->aggiungiPassiX((xBefore - 200) / 15);
    player->aggiungiPassiY(yBefore / 15);
    map->printBorder();     
    
    if(sostituisci)//se il player ha completato il taglio
    {
        pressedSpaceBar = false;
        this->changeMapValues(player, map, borderCutting);
    }
        
}

/*metodo per la "copertura" del taglio fatto dal player */
void PlayerMovement::changeMapValues(Player* player, Map* map, bool borderCutting)
{
    player->aggiungiPassiX((player->getX() - 200) / 15);
    player->aggiungiPassiY((player->getY()) / 15);

    if(!borderCutting) //se il taglio che è stato fatto non è lungo il bordo
    {
        int puntoY = 0;
        int puntoX = 0;
        
        //cerca un punto interno alla zona e controlla che sia la zona giusta
        for(int i = map->getRowsMin(); i < map->getRowsMax(); i++)
        {
            bool found = false;

            for(int j = map->getColsMin(); j < map->getColsMax(); j++)
            {
                bool uguale = false;

                //controlla che il punto attuale non sia presente nel cammino fatto dal player
                for(int p = 0; p < player->getPassiY().size(); p++)
                {
                    if(player->getPassiY()[p] == i && player->getPassiX()[p] == j)
                    {
                        uguale = true;
                        break;
                    }
                }

                //se il punto trovato non è nel cammino del player e il valore corrispondente
                //non è uno fra : mappa già tagliata(7), bonus(5), bordo(1), nemico(4) 
                if(!uguale && map->readFromMap(i, j) != 7 && map->readFromMap(i, j) != 5 &&
                    map->readFromMap(i, j) != 1 && map->readFromMap(i, j) != 4)
                { 
                    bool ctrl = true;
                    borderHandler->floodFillControllo(i, j, -2, -1, ctrl, map);
                    map->clearMap();

                    if(ctrl)
                    {
                        puntoX = j;
                        puntoY = i;
                        found = true;
                        break;
                    }
                }                    
            }
            if(found)
                break;
        }

        borderHandler->floodFill(puntoY, puntoX, 7, -1, map);

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