#include "../Header/GameHandler.h"

GameHandler::GameHandler(): width(800), height(600), FPS(60)
{
    srand(time(0));
    rows = 40;
    cols = 40;
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

    while(1)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        al_get_keyboard_state(&currently); //Panoramica attuale di ciò che sta succedendo sulla tastiera
        if(al_key_down(&currently, ALLEGRO_KEY_SPACE) &&
         (al_key_down(&currently, ALLEGRO_KEY_UP) || al_key_down(&currently, ALLEGRO_KEY_DOWN) || 
         al_key_down(&currently, ALLEGRO_KEY_LEFT) || al_key_down(&currently, ALLEGRO_KEY_RIGHT)))
            player->setCutting(true); //Se sono premuti contemporaneamente una delle freccette e la barra
        else
            player->setCutting(false);
        printBG(); 
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
        movePlayer(ev);
        //cout<<(player->getX()-200)/15<<" "<<player->getY()/15<<endl;

        moveEnemy(0, true);
        for(int i = 0; i < enemies.size(); i++)
        {
            moveEnemy(i, false); 
        }

        if (redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;           
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }

    }
}
void GameHandler::printBG()
{
    //al_draw_scaled_bitmap(background_bw, 200, 0, 600, 600, scaleX, scaleY, 0, 0, 0);
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
        if(j >= cols)
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
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
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
                player = new Player(j * 15 + 200, i * 15, "../Images/pc.png");
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
        int x2, y2;
        switch(ev.keyboard.keycode)
        {
            case ALLEGRO_KEY_UP:
                player->aggiungiPassiX((player->getX()-200)/15);
                player->aggiungiPassiY(player->getY()/15);
                x2 = (player->getX()  - 200) / 15;
                y2 = (player->getY() - player->getSpeed()) / 15;
                if(x2 > 39 || y2 > 39 || x2 < 0 || y2 < 0)
                    break;
                if(read_something_from_map(y2, x2) == 1)
                {
                    sostituisci = true;
                }
                else
                {
                    setCurrentPos(y2, x2, -1);
                }
                player->moveUp();
                break;
            case ALLEGRO_KEY_DOWN:
                player->aggiungiPassiX((player->getX()-200)/15);
                player->aggiungiPassiY(player->getY()/15);
                x2 = (player->getX()  - 200) / 15;
                y2 = (player->getY() + player->getSpeed()) / 15;
                if(x2 > 39 || y2 > 39 || x2 < 0 || y2 < 0)
                    break;
                if(read_something_from_map(y2, x2) == 1)
                {
                    sostituisci = true;
                }
                else
                {
                    setCurrentPos(y2, x2, -1);
                }
                player->moveDown();
                break;
            case ALLEGRO_KEY_LEFT:
                player->aggiungiPassiX((player->getX()-200)/15);
                player->aggiungiPassiY(player->getY()/15);
                x2 = (player->getX() - player->getSpeed() - 200) / 15;
                y2 = (player->getY() / 15);
                if(x2 > 39 || y2 > 39 || x2 < 0 || y2 < 0)
                    break;
                if(read_something_from_map(y2, x2) == 1)
                {
                    sostituisci = true;
                }
                else
                {
                    setCurrentPos(y2, x2, -1);
                }
                player->moveLeft();
                break;
            case ALLEGRO_KEY_RIGHT:
                player->aggiungiPassiX((player->getX()-200)/15);
                player->aggiungiPassiY(player->getY()/15);
                x2 = (player->getX() + player->getSpeed()  - 200) / 15;
                y2 = (player->getY() / 15);
                if(x2 > 39 || y2 > 39 || x2 < 0 || y2 < 0)
                    break;
                if(read_something_from_map(y2, x2) == 1)
                {
                    sostituisci = true;
                }
                else
                {
                    setCurrentPos(y2, x2, -1);
                }
                player->moveRight();
                break;
            default:
                break;
        }
        
        if(sostituisci)
        {
            for(int i = 0; i<player->getSizePassi();i++)
            {
                for(int j=0;j<player->getSizePassi();j++)
                    cout<<player->getPassiY()[i]<<" "<<player->getPassiX()[j]<<" ";
                cout<<endl;
            }
            cout<<endl<<endl;
            auto maxX = max_element(player->getPassiX().begin(),player->getPassiX().end());
            auto maxY = max_element(player->getPassiY().begin(),player->getPassiY().end());
            auto minX = min_element(player->getPassiX().begin(),player->getPassiX().end());
            auto minY = min_element(player->getPassiY().begin(),player->getPassiY().end());
            cout<<(*minY)<<" "<<(*minX)<<"      "<<(*maxY)<<" "<<(*maxX)<<endl;
            for(int i = (*minY); i < (*maxY); i++)
            {
                for(int j = (*minX); j < (*maxX); j++)
                {
                    logic_map[i][j] = -2;
                }
            }
            for(int i = 0; i < 40; i++)
            {
                for(int j = 0; j < 40; j++)
                {
                    if(logic_map[i][j]==-1)
                        logic_map[i][j]=1;
                }
            }

        }
    }
    else
    {
        switch(ev.keyboard.keycode)
        {
            case ALLEGRO_KEY_UP:
                if(collision(player->getX(), player->getY() - (player->getSpeed()*3), true))
                    player->moveUp();
                break;
            case ALLEGRO_KEY_DOWN:
                if(collision(player->getX(), player->getY() + (player->getSpeed()*3), true))
                    player->moveDown();
                break;
            case ALLEGRO_KEY_RIGHT:
                if(collision(player->getX() + (player->getSpeed()*3), player->getY(), true))
                    player->moveRight();
                break;
            case ALLEGRO_KEY_LEFT:
                if(collision(player->getX() - (player->getSpeed()*3), player->getY(), true))
                    player->moveLeft();
                break;
            default:
                break;
        }
    }
    player->print();
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
