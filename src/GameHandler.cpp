#include "../Header/GameHandler.h"

GameHandler::GameHandler(): width(816), height(616), FPS(15)
{
    //srand(time(0));
    rowsMax = 40;
    rowsMin = 0;
    colsMax = 40;
    colsMin = 0;
    redraw = true;
    display = al_create_display(width, height);
    if(!display)
    {
        cout<<"failed to create display";
        return;
    }
    timer = al_create_timer(1.0 / FPS);
    load_map();
    read_map();
    background_bw = al_load_bitmap("../Images/backgroundBW.png");
    if (!background_bw)
    {
        cout<<"failed background bw";
        return;
    }
    background = al_load_bitmap("../Images/background.png");
    if (!background)
    {
        cout<<"failed background";
        return;
    }

}
void GameHandler::Game()
{
    printBG();
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    ALLEGRO_EVENT ev, evPrec;
    while(1)
    {
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
        al_get_keyboard_state(&currently); //Panoramica attuale di ciò che sta succedendo sulla tastiera
        if(al_key_down(&currently, ALLEGRO_KEY_SPACE) &&
         (al_key_down(&currently, ALLEGRO_KEY_UP) || al_key_down(&currently, ALLEGRO_KEY_DOWN) || 
         al_key_down(&currently, ALLEGRO_KEY_LEFT) || al_key_down(&currently, ALLEGRO_KEY_RIGHT)))
            player->setCutting(true); //Se sono prewhy when i press a key on my keyboard  it values is for 3muti contemporaneamente una delle freccette e la barra
        else
        {
            player->setCutting(false);
        }
        //if(evPrec.keyboard.keycode == ALLEGRO_KEY_LEFT || evPrec.keyboard.keycode == ALLEGRO_KEY_UP || evPrec.keyboard.keycode == ALLEGRO_KEY_RIGHT
           //|| evPrec.keyboard.keycode == ALLEGRO_KEY_DOWN)
        movePlayer(evPrec);
        
        for(int i = 0; i < enemies.size(); i++)
        {
            //moveEnemy(i, false); 
        }
        }
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            evPrec = ev;
        }
        if(ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            evPrec.keyboard.keycode = 80;
        }
        if(ev.keyboard.keycode == ALLEGRO_KEY_L)
        {
            for(int i=0;i<40;i++)
            {
                for(int j=0;j<40;j++)
                {
                    cout<<logic_map[i][j]<<" ";
                }
                cout<<endl;
            }
        }
        if (redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;           
            printBG();
            player->print();
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }
    }
    
}
void GameHandler::printBG()
{
    al_draw_bitmap(background_bw, 200, 0, 0);
}
void GameHandler::scale()
{
    /*
    int sx = disp_data.width / width;
    int sy = disp_data.height / height;
    int _scale = min(sx, sy);
    scaleW = 600 * _scale;
    scaleH = 600 * _scale;
    scaleX = (disp_data.width / 2) -200;
    scaleY = disp_data.height / 2;
    */
}
void GameHandler::load_map()
{
    ifstream map("../maps/map1.txt");
    char ch;
    int c;
    int i = 0;
    int j = 0;
    while(!map.eof())
    {
        map>>logic_map[i][j];
        j++;
        if(j >= colsMax)
        {
            j = 0;
            i++;
        }
    }
    map.close();
}
void GameHandler::read_map()
{
    bool create = true;
    bool create2 = create;
    for (int i = 0; i < rowsMax; i++)
    {
        for (int j = 0; j < colsMax; j++)
        {

            if (logic_map[i][j] == 3 && create)
            {
                boss = new Enemy(j * 15 + 200, i * 15 , "../Images/enemy.png", true, 1);
                create = false;
            }
            else if (logic_map[i][j] == 4 && enemies.size() < 9)
            {
                enemies.push_back(new Enemy(j * 15 + 200, i * 15, "../Images/enemy2.png", false, 1));
            }
            else if (logic_map[i][j] == 1 && create2)
            {
                player = new Player((j * 15 + 200), i * 15, "../Images/pc.png");
                create2 = false;
            }
        }
    }
}
int GameHandler::read_something_from_map(int i, int j)
{
    return logic_map[i][j];
}
void GameHandler::setCurrentPos(int i, int j, int value)
{
    logic_map[i][j] = value;
}
void GameHandler::movePlayer(ALLEGRO_EVENT ev)
{
    if(player->getCutting())
    {
        bool sostituisci = false;
        int x2 = 0, y2 = 0;
        switch(ev.keyboard.keycode)
        {                           
            case ALLEGRO_KEY_UP:
                y2 -= (player->getSpeed());
                sostituisci = playerCutting(x2,y2);
                if(x2 > 39 || y2 > 39 || x2 < 0 || y2 < 0)
                    break;
                player->moveUp();
                break;
            case ALLEGRO_KEY_DOWN:
                y2 += (player->getSpeed());
                sostituisci = playerCutting(x2,y2);
                if(x2 > 39 || y2 > 39 || x2 < 0 || y2 < 0)
                    break;
                player->moveDown();
                break;
            case ALLEGRO_KEY_LEFT:
                x2 -= (player->getSpeed());
                sostituisci = playerCutting(x2,y2);
                if(x2 > 39 || y2 > 39 || x2 < 0 || y2 < 0)
                    break;
                player->moveLeft();
                break;
            case ALLEGRO_KEY_RIGHT:
                x2 += (player->getSpeed());
                sostituisci = playerCutting(x2,y2);
                if(x2 > 39 || y2 > 39 || x2 < 0 || y2 < 0)
                    break;
                player->moveRight();
                break;
            default:
                break;
        }
        //cout<<y2<<" "<<x2<<endl;
        if(sostituisci)
        {
            cont++;
            
                    /*for(int i = 0; i < player->getSizePassi(); i++)
                    {
                        for(int j = 0;j < player->getSizePassi(); j++)
                            cout<<player->getPassiY()[i]<<" "<<player->getPassiX()[j]<<" ";
                        cout<<endl;
                    }
                    cout<<endl<<endl;*/
            auto maxX = max_element(player->getPassiX().begin(),player->getPassiX().end()); 
            auto maxY = max_element(player->getPassiY().begin(),player->getPassiY().end());
            auto minX = min_element(player->getPassiX().begin(),player->getPassiX().end());
            auto minY = min_element(player->getPassiY().begin(),player->getPassiY().end());
            cout<<*minY<<" "<<*maxY<<" "<<*minX<<" "<<*maxX<<endl;
            for(int i = (*minY); i <= (*maxY); i++)
            {
                for(int j = (*minX); j <= (*maxX); j++)
                {
                    if(*minX == 0 && *maxX < 39)
                    {
                        if(*minY == 0 && *maxY < 39 && i < *maxY && j < *maxX) //6
                            logic_map[i][j] = 7;
                        else if(*minY > 0 && *maxY == 39 && i > *minY && j < *maxX) //7
                            logic_map[i][j] = 7;
                        else if(*minY > 0 && *maxY < 39 && i > *minY && i < *maxY && j < *maxX) //8
                            logic_map[i][j] = 7;
                    }
                    else if(*minX > 0 && *maxX == 39)
                    {
                        if(*minY == 0 && *maxY < 39 && i < *maxY && j > *minX) //10
                            logic_map[i][j] = 7;
                        else if(*minY > 0 && *maxY == 39 && i > *minY && j > *minX) //11
                            logic_map[i][j] = 7;
                        else if(*minY > 0 && *maxY < 39 && i > *minY && i < *maxY && j > *minX) //12
                            logic_map[i][j] = 7;
                    }
                    else if(*minX > 0 && *maxX < 39)
                    {
                        if(*minY == 0 && *maxY < 39 && i < *maxY && j > *minX && j < *maxX) //14
                            logic_map[i][j] = 7;
                        else if(*minY > 0 && *maxY == 39 && i > *minY && j > *minX && j < *maxX) //15
                            logic_map[i][j] = 7;
                    }
                    if(*minX == *maxX)
                    {
                        if(*minY == 0 && *maxY == 39) //17
                            logic_map[i][j-1] = 7;
                    }
                    if(*minY == *maxY)
                    {
                        if(*minX == 0 && *maxX == 39) //18
                            logic_map[i-1][j] = 7;
                    }

                    
                }
            }
        
            //cout<<endl;
            /*for(int i = (*minY); i <= (*maxY); i++)
            {
                for(int j = (*minX); j <= (*maxX); j++)
                {
                    if(logic_map[i][j] != -1)
                    {
                        logic_map[i][j] = 7;*/
                        //cout<<logic_map[i][j]<<" ";
                    /*if(*minX == 0 && *maxX < 39)
                    {
                        if(*minY == 0 && *maxY < 39 && i < *maxY && j < *maxX) //6
                            logic_map[i][j] = 7;
                        else if(*minY > 0 && *maxY == 39 && i > *minY && j < *maxX) //7
                            logic_map[i][j] = 7;
                        else if(*minY > 0 && *maxY < 39 && i > *minY && i < *maxY && j < *maxX) //8
                            logic_map[i][j] = 7;
                    }
                    else if(*minX > 0 && *maxX == 39)
                    {
                        if(*minY == 0 && *maxY < 39 && i < *maxY && j > *minX) //10
                            logic_map[i][j] = 7;
                        else if(*minY > 0 && *maxY == 39 && i > *minY && j > *minX) //11
                            logic_map[i][j] = 7;
                        else if(*minY > 0 && *maxY < 39 && i > *minY && i < *maxY && j > *minX) //12
                            logic_map[i][j] = 7;
                    }
                    else if(*minX > 0 && *maxX < 39)
                    {
                        if(*minY == 0 && *maxY < 39 && i < *maxY && j > *minX && j < *maxX) //14
                            logic_map[i][j] = 7;
                        else if(*minY > 0 && *maxY == 39 && i > *minY && j > *minX && j < *maxX) //15
                            logic_map[i][j] = 7;
                    }
                    }
                    
                }
                //cout<<endl;
            }*/
            //17 e 18 funzionano ma non si riesce a provarli senza stoppare i nemici, il gioco si blocca
            /*if(*minX == *maxX)                      
                if(*minY == 0 && *maxY == 39) //17
                    for(int i = 0; i <= 39; i++)
                        for(int j = 0; j < *maxX; j++)
                            logic_map[i][j] = 7;*/
            /*if(*minY == *maxY)
                if(*minX == 0 && *maxX == 39) //18
                    for(int i = 0; i < *maxY; i++)
                        for(int j = 0; j <= 39; j++)
                            logic_map[i][j] = 7;*/
            if(cont >= 1)
            {
                for(int i = 0; i < 40; i++)
                {
                    for(int j = 0; j < 40; j++)
                    {
                        if(logic_map[i][j] == -1)
                            logic_map[i][j] = 1;
                    }
                }
                player->svuotaPassi();
                cont = 0;
            }
        }
    }
        else
        {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_UP:
                    if(collision(player->getX(), player->getY() - player->getSpeed(), true))
                        player->moveUp();
                    break;
                case ALLEGRO_KEY_DOWN:
                    if(collision(player->getX(), player->getY() + player->getSpeed(), true))
                        player->moveDown();
                    break;
                case ALLEGRO_KEY_RIGHT:
                    if(collision(player->getX() + player->getSpeed(), player->getY(), true))
                        player->moveRight();
                    break;
                case ALLEGRO_KEY_LEFT:
                    if(collision(player->getX() - player->getSpeed(), player->getY(), true))
                        player->moveLeft();
                    break;
                default:
                    break;
            }
        }
}
bool GameHandler::playerCutting(int &x, int &y)
{
    player->aggiungiPassiX((player->getX()-200)/15);
    player->aggiungiPassiY(player->getY()/15);
    x = (player->getX() - 200 + x) / 15;
    y = (player->getY() + y) / 15;
    if(read_something_from_map(y, x) == 1) //PROBLEMA entra alla prima iterazione 
    {
        return true;
    }
    else
    {
        setCurrentPos(y, x, -1);
    }
    return false;
      
}
void GameHandler::moveEnemy(int i, bool is_boss)
{
    bool trovato = false;
    bool collisione = false;
    int dir = 0;
    if (is_boss)
    {
        dir = boss->get_dir();
    }
    else
    {
        dir = enemies[i]->get_dir();
    }
    switch (dir)
    {
        case 1:
            
            if((collision(boss->getX() + boss->getSpeed(), boss->getY(), false) == false) || (collision(enemies[i]->getX() + enemies[i]->getSpeed(), enemies[i]->getY(), false) == false))
            {
                collisione = true;
            }
            break;
        case 2:
            if((collision(boss->getX() + boss->getSpeed(), boss->getY() + boss->getSpeed(), false) == false) || (collision(enemies[i]->getX() + enemies[i]->getSpeed(), enemies[i]->getY() + enemies[i]->getSpeed(), false) == false))
            {
                collisione = true;
            }            
            break;
        case 3:
            if((collision(boss->getX(), boss->getY() + boss->getSpeed(), false) == false) || (collision(enemies[i]->getX(), enemies[i]->getY() + enemies[i]->getSpeed(), false) == false))
            {
                collisione = true;
            }
            break;
        case 4:
            if((collision(boss->getX() - boss->getSpeed(), boss->getY() + boss->getSpeed(), false) == false) || (collision(enemies[i]->getX() - enemies[i]->getSpeed(), enemies[i]->getY() + enemies[i]->getSpeed(), false) == false))
            {
                collisione = true;
            }
            break;
        case 5:
            if((collision(boss->getX() - boss->getSpeed(), boss->getY(), false) == false) || (collision(enemies[i]->getX() - enemies[i]->getSpeed(), enemies[i]->getY(), false) == false))
            {
                collisione = true;
            }
            break;
        case 6:
            if((collision(boss->getX() - boss->getSpeed(), boss->getY() - boss->getSpeed(), false) == false) || (collision(enemies[i]->getX() - enemies[i]->getSpeed(), enemies[i]->getY() - enemies[i]->getSpeed(), false) == false))
            {
                collisione = true;
            }
            break;
        case 7:
            if((collision(boss->getX(), boss->getY() - boss->getSpeed(), false) == false) || (collision(enemies[i]->getX(), enemies[i]->getY() - enemies[i]->getSpeed(), false) == false))
            {
                collisione = true;
            }
            break;
        case 8:
            if((collision(boss->getX() + boss->getSpeed(), boss->getY() - boss->getSpeed(), false) == false) || (collision(enemies[i]->getX() + enemies[i]->getSpeed(), enemies[i]->getY() - enemies[i]->getSpeed(), false) == false))
            {
                collisione = true;
            }
            break;
        default:
            break;
    }
    if(collisione)
    {
        while (!trovato)
        {
            int new_dir = (rand()%8) + 1;
            switch (new_dir)
            {
                case 1:
                    if(is_boss)
                    {  
                        if(collision(boss->getX() + boss->getSpeed(), boss->getY(), false))
                        {
                            boss->set_dir(new_dir);
                            trovato = true;
                        }
                    }
                    else
                    {
                        if(collision(enemies[i]->getX() + enemies[i]->getSpeed(), enemies[i]->getY(), false))
                        {
                            enemies[i]->set_dir(new_dir);
                            trovato = true;
                        }
                    }
                    break;
                case 2:
                    if(is_boss)
                    {
                        if(collision(boss->getX() + boss->getSpeed(), boss->getY() + boss->getSpeed(), false))
                        {
                            boss->set_dir(new_dir);
                            trovato = true;
                        }
                    }
                    else
                    {
                        if(collision(enemies[i]->getX() + enemies[i]->getSpeed(), enemies[i]->getY() + enemies[i]->getSpeed(), false))
                        {
                            enemies[i]->set_dir(new_dir);
                            trovato = true;
                        }
                    }
                    break;
                case 3:
                    if(is_boss)
                    {
                        if(collision(boss->getX(), boss->getY() + boss->getSpeed(), false))
                        {
                            boss->set_dir(new_dir);
                            trovato = true;
                        }
                    }
                    else
                    {
                        if(collision(enemies[i]->getX(), enemies[i]->getY() + enemies[i]->getSpeed(), false))
                        {
                            enemies[i]->set_dir(new_dir);
                            trovato = true;
                        }
                    }
                    break;
                case 4:
                    if(is_boss)
                    {
                        if(collision(boss->getX() - boss->getSpeed(), boss->getY() + boss->getSpeed(), false))
                        {
                            boss->set_dir(new_dir);
                            trovato = true;
                        }
                    }
                    else
                    {
                        if(collision(enemies[i]->getX() - enemies[i]->getSpeed(), enemies[i]->getY() + enemies[i]->getSpeed(), false))
                        {
                            enemies[i]->set_dir(new_dir);
                            trovato = true;
                        }
                    }
                    break;
                case 5:
                    if(is_boss)
                    {
                        if(collision(boss->getX() - boss->getSpeed(), boss->getY(), false))
                        {
                            boss->set_dir(new_dir);
                            trovato = true;
                        }
                    }
                    else
                    {
                        if(collision(enemies[i]->getX() - enemies[i]->getSpeed(), enemies[i]->getY(), false))
                        {
                            enemies[i]->set_dir(new_dir);
                            trovato = true;
                        }
                    }
                    break;
                case 6:
                    if(is_boss)
                    {
                        if(collision(boss->getX() - boss->getSpeed(), boss->getY() - boss->getSpeed(), false))
                        {
                            boss->set_dir(new_dir);
                            trovato = true;
                        }
                    }
                    else
                    {
                        if(collision(enemies[i]->getX() - enemies[i]->getSpeed(), enemies[i]->getY() - enemies[i]->getSpeed(), false))
                        {
                            enemies[i]->set_dir(new_dir);
                            trovato = true;
                        }
                    }
                    break;
                case 7:
                    if(is_boss)
                    {
                        if(collision(boss->getX(), boss->getY() - boss->getSpeed(), false))
                        {
                            boss->set_dir(new_dir);
                            trovato = true;
                        }
                    }
                    else
                    {
                        if(collision(enemies[i]->getX(), enemies[i]->getY() - enemies[i]->getSpeed(), false))
                        {
                            enemies[i]->set_dir(new_dir);
                            trovato = true;
                        }
                    }
                    break;
                case 8:
                    if(is_boss)
                    {
                        if(collision(boss->getX() + boss->getSpeed(), boss->getY() - boss->getSpeed(), false))
                        {
                            boss->set_dir(new_dir);
                            trovato = true;
                        }
                    }
                    else
                    {
                        if(collision(enemies[i]->getX() + enemies[i]->getSpeed(), enemies[i]->getY() - enemies[i]->getSpeed(), false))
                        {
                            enemies[i]->set_dir(new_dir);
                            trovato = true;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
    if(is_boss)
        boss->move();
    else
        enemies[i]->move();

}
bool GameHandler::collision(int x, int y, bool isPlayer)
{
    /*if (isPlayer)
    {
        if (x < 200 || y < 0 || x > width - player->getSize() || y > height - player->getSize())
            return false;
    }*/
    int x2 = x;
    int y2 = y;
    if (isPlayer)
    {
        x = (x - 200) / 15;
        y = y / 15;
        //cout<<x<<" "<<y<< "(1)"<<endl;
        if( x > 39 || y > 39 || x < 0 || y < 0)
            return false;
    } 
    else
    {
        x = (x - 200 - 32) / 15;
        y = (y - 32) / 15;
    }
    int something = read_something_from_map(y, x);
    if(something != 1 && isPlayer)
        return false;
    
    x2 = (x2 - 200 + 64) / 15;
    y2 = (y2 + 64) / 15;

    if(((read_something_from_map(y, x) != 0 && read_something_from_map(y, x) != 3 )
    || (read_something_from_map(y2, x) != 0 && read_something_from_map(y2, x) != 3 )
    || (read_something_from_map(y, x2) != 0 && read_something_from_map(y, x2) != 3 )
    || (read_something_from_map(y2, x2) != 0 && read_something_from_map(y2, x2) != 3 ))
    && !isPlayer)
        return false;
    return true;
}
void GameHandler::min_max(int &i, int &j, bool min)
{
    vector<int> pY;
    vector<int> pX;
    if(min)
    {
        for(int i = 0; i < 40; i++)
        {
            bool considera = false;
            for(int j = 0; j < 40; j++)
            {
                if(logic_map[i][j] == 1)
                {
                    considera = true;
                    pX.push_back(j);
                }
            }
            if(considera)
                pY.push_back(i);
        }
        i = *min_element(pY.begin(), pY.end());
        j = *min_element(pX.begin(), pX.end());
    }
    else
    {
        for(int i = 0; i < 40; i++)
        {
            bool considera = false;
            for(int j = 0; j < 40; j++)
            {
                if(logic_map[i][j] == 1)
                {
                    considera = true;
                    pX.push_back(j);
                }
            }
            if(considera)
                pY.push_back(i);
        }
        i = *max_element(pY.begin(), pY.end());
        j = *max_element(pX.begin(), pX.end());
    }
    
}

void GameHandler::updateRows_Cols()
{
    int copiaRowsMax = rowsMax;
    int copiaRowsMin = rowsMin;
    int copiaColsMax = colsMax;
    int copiaColsMin = colsMin;

    bool rigaMin = true;
    bool rigaMax = true;
    bool colonnaMin = true;
    bool colonnaMax = true;
    for(int i = rowsMin; i < rowsMax; i++)
    {
        bool rigaNonMinima = true;
        for(int j = colsMin; j < colsMax; j++)
        {
            if(logic_map[i][j] == 0)
                rigaNonMinima = false;

        }
        if( !rigaNonMinima  && rigaMin)
        {
            rowsMin = (i - 1);
            rigaMin = false;
        }
    }
    for(int i = colsMin; i < colsMax; i++)
    {
        bool colonnaNonMinima = true;
        for(int j = rowsMin; j < rowsMax; j++)
        {
            if(logic_map[i][j] == 0)
                colonnaNonMinima = false;

        }
        if( !colonnaNonMinima  && colonnaMin)
        {
            colsMin = (i - 1);
            colonnaMin = false;
        }
    }
    for(int i = (rowsMax-1); i >= rowsMin; i--)
    {
        bool rigaNonMassima = true;
        for(int j = colsMin; j < colsMax; j++)
        {
            if(logic_map[i][j] == 0)
                rigaNonMassima = false;

        }
        if( !rigaNonMassima  && rigaMax)
        {
            rowsMax = (i + 2);
            rigaMax = false;
        }
    }
    for(int i = (colsMax-1); i >= colsMin; i--)
    {
        bool colonnaNonMassima = true;
        for(int j = rowsMin; j < rowsMax; j++)
        {
            if(logic_map[i][j] == 0)
                colonnaNonMassima = false;

        }
        if(!colonnaNonMassima  && colonnaMax)
        {
            colsMax = (i + 2);
            colonnaMax = false;
        }
    }
}

