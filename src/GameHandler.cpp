#include "../Header/GameHandler.h"

GameHandler::GameHandler(): width(816), height(616), FPS(30)
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
    board = al_load_bitmap("../Images/board.png");
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
        
        /*for(int i = 0; i < enemies.size(); i++)
        {
            moveEnemy(i, false); 
        }
        moveEnemy(0, true);*/
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
            cout<<endl;
        }
        if (redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;           
            printBG();
            printBoard();
            boss->print();
            for(int i = 0; i < enemies.size(); i++)
            {
                enemies[i]->print();
            }
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
void GameHandler::printBoard()
{
    for(int i = rowsMin; i < rowsMax; i++)
    {
        for(int j = colsMin; j < colsMax; j++)
        {
            if(logic_map[i][j] == 1)
                al_draw_bitmap(board, (j * 15) + 200, (i * 15) , 0);
        }
    }
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
    for (int i = rowsMin; i < rowsMax; i++)
    {
        for (int j = colsMin; j < colsMax; j++)
        {

            if (logic_map[i][j] == 3 && create)
            {
                boss = new Enemy(j * 15 + 200, i * 15 , "../Images/enemy.png", true, 3);
                create = false;
            }
            else if (logic_map[i][j] == 4 && enemies.size() < 9)
            {
                enemies.push_back(new Enemy(j * 15 + 200, i * 15, "../Images/enemy2.png", false, 3));
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
    //cout<<cont<<endl;
    if(player->getCutting())
    {
        bool sostituisci = false;
        int x2 = 0, y2 = 0;
        /*switch(ev.keyboard.keycode)
        {                           
            case ALLEGRO_KEY_UP:
                y2 -= (player->getSpeed());
                sostituisci = playerCutting(x2, y2);
                if(x2 > 39 || y2 > 39 || x2 < 0 || y2 < 0)
                    break;
                player->moveUp();
                break;
            case ALLEGRO_KEY_DOWN:
                y2 += (player->getSpeed());
                sostituisci = playerCutting(x2, y2);
                if(x2 > 39 || y2 > 39 || x2 < 0 || y2 < 0)
                    break;
                player->moveDown();
                break;
            case ALLEGRO_KEY_LEFT:
                x2 -= (player->getSpeed());
                sostituisci = playerCutting(x2, y2);
                if(x2 > 39 || y2 > 39 || x2 < 0 || y2 < 0)
                    break;
                player->moveLeft();
                break;
            case ALLEGRO_KEY_RIGHT:
                x2 += (player->getSpeed());
                sostituisci = playerCutting(x2, y2);
                if(x2 > 39 || y2 > 39 || x2 < 0 || y2 < 0)
                    break;
                player->moveRight();
                break;
            default:
                break;
        }*/
        switch(ev.keyboard.keycode)
        {                           
            case ALLEGRO_KEY_UP:
                y2 -= (player->getSpeed());
                x2 = (player->getX() - 200 + x2) / 15;
                y2 = (player->getY() + y2) / 15;
                //cout<<logic_map[y2][x2]<<endl;
                if(x2 > colsMax-1 || y2 > rowsMax-1 || x2 < colsMin || y2 < rowsMin || logic_map[y2][x2] == 7)
                    break;
                if(read_something_from_map(y2, x2) == 1) //PROBLEMA entra alla prima iterazione 
                {
                    setCurrentPos(y2, x2, -1);
                    sostituisci = true;
                }
                else
                {
                    setCurrentPos(y2, x2, -1);
                }
                if (comodo)
                {
                    directionPlayer();
                    setCurrentPos((player->getY()) / 15, (player->getX() - 200) / 15, -1);
                    comodo = false;
                }
                player->aggiungiPassiX((player->getX() - 200) / 15);
                player->aggiungiPassiY((player->getY()) / 15);
                player->moveUp();
                break;
            case ALLEGRO_KEY_DOWN:
                y2 += (player->getSpeed());
                x2 = (player->getX() - 200 + x2) / 15;
                y2 = (player->getY() + y2) / 15;
                //cout<<logic_map[y2][x2]<<endl;
                if(x2 > colsMax-1 || y2 > rowsMax-1 || x2 < colsMin || y2 < rowsMin || logic_map[y2][x2] == 7)
                    break;
                if(read_something_from_map(y2, x2) == 1) //PROBLEMA entra alla prima iterazione 
                {
                    setCurrentPos(y2, x2, -1);
                    sostituisci = true;
                }
                else
                {
                    setCurrentPos(y2, x2, -1);
                }
                if (comodo)
                {
                    directionPlayer();
                    setCurrentPos((player->getY()) / 15, (player->getX() - 200) / 15, -1);
                    comodo = false;
                }
                
                player->aggiungiPassiX((player->getX() - 200) / 15);
                player->aggiungiPassiY((player->getY()) / 15);
                player->moveDown();
                break;
            case ALLEGRO_KEY_LEFT:
                x2 -= (player->getSpeed());
                x2 = (player->getX() - 200 + x2) / 15;
                y2 = (player->getY() + y2) / 15;
                //cout<<logic_map[y2][x2]<<endl;
                if(x2 > colsMax-1 || y2 > rowsMax-1 || x2 < colsMin || y2 < rowsMin || logic_map[y2][x2] == 7)
                    break;
                if(read_something_from_map(y2, x2) == 1) //PROBLEMA entra alla prima iterazione 
                {
                    setCurrentPos(y2, x2, -1);
                    sostituisci = true;
                }
                else
                {
                    setCurrentPos(y2, x2, -1);
                }
                if (comodo)
                {
                    directionPlayer();
                    setCurrentPos((player->getY()) / 15, (player->getX() - 200) / 15, -1);
                    comodo = false;
                }
                player->aggiungiPassiX((player->getX() - 200) / 15);
                player->aggiungiPassiY((player->getY()) / 15);
                player->moveLeft();
                break;
            case ALLEGRO_KEY_RIGHT:
                x2 += (player->getSpeed());
                x2 = (player->getX() - 200 + x2) / 15;
                y2 = (player->getY() + y2) / 15;
                //cout<<logic_map[y2][x2]<<endl;
                if(x2 > colsMax-1 || y2 > rowsMax-1 || x2 < colsMin || y2 < rowsMin || logic_map[y2][x2] == 7)
                    break;
                if(read_something_from_map(y2, x2) == 1) //PROBLEMA entra alla prima iterazione 
                {
                    setCurrentPos(y2, x2, -1);
                    sostituisci = true;
                }
                else
                {
                    setCurrentPos(y2, x2, -1);
                }
                if (comodo)
                {
                    directionPlayer();
                    setCurrentPos((player->getY()) / 15, (player->getX() - 200) / 15, -1);
                    comodo = false;
                }
                player->aggiungiPassiX((player->getX() - 200) / 15);
                player->aggiungiPassiY((player->getY()) / 15);
                player->moveRight();
                break;
            default:
                break;
        }     
        
        //cout<<y2<<" "<<x2<<endl;
        if(sostituisci)
        {
           // cout<<(player->getY() / 15);
            //cout<<" "<<((player->getX() - 200) / 15)<<endl;
            player->aggiungiPassiX((player->getX() - 200) / 15);
            player->aggiungiPassiY((player->getY()) / 15);
            cont++;
            //cout<<cont<<endl;
                   
            auto maxX = max_element(player->getPassiX().begin(),player->getPassiX().end()); 
            auto maxY = max_element(player->getPassiY().begin(),player->getPassiY().end());
            auto minX = min_element(player->getPassiX().begin(),player->getPassiX().end());
            auto minY = min_element(player->getPassiY().begin(),player->getPassiY().end());
            //cout<<*minY<<" "<<*maxY<<" "<<*minX<<" "<<*maxX<<endl;
            /*for(int i = (*minY); i <= (*maxY); i++)
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
            }*/
           // logic_map[(*maxY)][(*minX)] = -1;
            //logic_map[(*minY)][(*maxX)] = -1;
            //cout<<endl;
            for(int i = (*minY); i <= (*maxY); i++)
            {
                for(int j = (*minX); j <= (*maxX); j++)
                {
                   /* if(*minX == 0 && *maxX < 39)
                    {
                        if(*minY == 0 && *maxY < 39)
                        {
                            logic_map[(*maxY)][(*minX)] = -1;
                            logic_map[(*minY)][(*maxX)] = -1;
                        }
                        else if(*minY > 0 && *maxY == 39)
                        {
                            logic_map[(*maxY)][(*maxX)] = -1;
                            logic_map[(*minY)][(*minX)] = -1;
                        }
                        else if(*minY > 0 && *maxY < 39)
                        {
                            logic_map[(*minY)][(*minX)] = -1;
                            logic_map[(*maxY)][(*minX)] = -1;
                        }
                    }
                    else if(*minX > 0 && *maxX == 39)
                    {
                        if(*minY == 0 && *maxY < 39)
                        {
                            logic_map[(*maxY)][(*maxX)] = -1;
                            logic_map[(*minY)][(*minX)] = -1;
                        }
                        else if(*minY > 0 && *maxY == 39)
                        {
                            logic_map[(*minY)][(*maxX)] = -1;
                            logic_map[(*maxY)][(*minX)] = -1;
                        }
                        else if(*minY > 0 && *maxY < 39)
                        {
                            logic_map[(*minY)][(*maxX)] = -1;
                            logic_map[(*maxY)][(*maxX)] = -1;
                        }
                    }
                    else if(*minX > 0 && *maxX < 39)
                    {
                        if(*minY == 0 && *maxY < 39)
                        {
                            logic_map[(*minY)][(*minX)] = -1;
                            logic_map[(*minY)][(*maxX)] = -1;
                        }
                        else if(*minY > 0 && *maxY == 39)
                        {
                            logic_map[(*maxY)][(*minX)] = -1;
                            logic_map[(*maxY)][(*maxX)] = -1;
                        }
                        else if(*minY > 0 && *maxY < 39)
                        {
                            logic_map[(*minY)][(*minX)] = -1;
                            logic_map[(*minY)][(*maxX)] = -1;
                        }
                    }*/
                    
                    //mancano le combinazioni con Y e l'ultima di X
                    //if(logic_map[i][j] != -1 )
                    //{
                        
                        //logic_map[i][j] = 7;
                        
                    //}
                    
                }
                //cout<<endl;
            }
            //player->svuotaPassi();   
            //17 e 18 funzionano ma non si riesce a provarli senza stoppare i nemici, il gioco si blocca
            /*if(*minX == *maxX)                      
            {
                //if(*minY == 0 && *maxY == 39) //17
                    for(int i = rowsMin; i <= *maxY; i++)
                        for(int j = colsMin; j < *maxX; j++)
                            //logic_map[i][j] = 7;
            }
            if(*minY == *maxY)
                //if(*minX == 0 && *maxX == 39) //18
                    for(int i = rowsMin; i < *maxY; i++)
                        for(int j = colsMin; j < colsMax; j++)
                            //logic_map[i][j] = 7;*/
            bool trovato = false;
            int medioY = 0;
            int medioX = 0;
            int bossX = (boss->getX() - 200) / 15;
            int bossY = boss->getY() / 15;
            bool bossInside = false;
            /*if(bossX >= *minX && bossX <= *maxX && bossY >= *minY && bossY <= *maxY)
                bossInside = true;
            cout<<bossInside<<endl;

            for(int i = rowsMin; i < rowsMax; i++)
            {
                for(int j = colsMin; j < colsMax; j++)
                {
                                            cout<<i<<" "<<j<<endl;
                                                                    cout<<*minY<<" "<<*maxY<<" "<<*minX<<" "<<*maxX<<endl;


                    if(!bossInside && ( j > *minX && j < *maxX && i > *minY && i < *maxY))
                    {

                        trovato = true;
                        medioY = i;
                        medioX = j;
                        break;
                    }
                    else if(bossInside && ( j < *minX && j > *maxX && i < *minY && i > *maxY))
                    {
                        trovato = true;
                        medioY = i;
                        medioX = j;
                        break;
                    }
                }
                if(trovato)
                    break;
            }*/
            /*for(int i = 0, j = 0; i < player->getPassiX().size(); i++, j++)
            {
                int p = player->getPassiY()[i];
                int k = player->getPassiX()[j];
                //cout<<logic_map[p][k]<<" ";
                if(p != 39 && p != 0 && k != 0 && k != 39)
                {
                    //cout<<p<<" "<<k<<endl;
                    if(logic_map[p][k+1] == -1 && logic_map[p+1][k] == 0)
                    {
                        medioY = p+1;
                        medioX = k;
                        break;
                    }
                    else
                    {
                        //cout<<"nt ";
                    }
                    
                }
            }*/
            /*for(int i = rowsMin; i < rowsMax; i++)
            {
                bool trovato = false;
                for(int j = colsMin; j < colsMax; j++)
                {
                    for(int k = 0; k < )
                    if(isPointInPath(player->getPassiY(), player->getPassiX(), i , j))
                    {
                        medioY = i;
                        medioX = j;
                        trovato = true;
                        break;
                    }
                    
                }
                if(trovato)
                    break;
            }*/
            vector< pair<int,int> > vertex;
            bool cambioRiga = false;
            bool cambioColonna = false;
            pair<int, int> vertexInFin;
            vertexInFin.first = player->getPassiY()[0];
            vertexInFin.second = player->getPassiX()[0];
            vertex.push_back(vertexInFin);
            
            for(int i = 0; i < player->getPassiY().size() - 1; i++) //vertici
            {
                vertexInFin.first = player->getPassiY()[i];
                vertexInFin.second = player->getPassiX()[i];
                if(vertexInFin.first != player->getPassiY()[i+1])
                    cambioRiga = true;
                if(vertexInFin.second != player->getPassiX()[i+1])
                    cambioColonna = true;
                if(cambioRiga && cambioColonna)
                {
                    cambioRiga = false;
                    cambioColonna = false;
                    vertex.push_back(vertexInFin);
                }

            }
            vertexInFin.first = player->getPassiY()[player->getPassiY().size() -1];
            vertexInFin.second = player->getPassiX()[player->getPassiX().size() -1];
            vertex.push_back(vertexInFin);

            /*pair<int, int> tmp;
            tmp.first = *minY;
            tmp.second = *minX;
            if(find(vertex.begin(), vertex.end(), tmp) == vertex.end())
            {
                vertexInFin.first = *minY;
                vertexInFin.second = *minX;
                vertex.push_back(vertexInFin);
            } //primo

            tmp.first = *minY;
            tmp.second = *maxX;
            if(find(vertex.begin(), vertex.end(), tmp) == vertex.end())
            {
                vertexInFin.first = *minY;
                vertexInFin.second = *maxX;
                vertex.push_back(vertexInFin);
            } //secondo

            tmp.first = *maxY;
            tmp.second = *minX;
            if(find(vertex.begin(), vertex.end(), tmp) == vertex.end())
            {
                vertexInFin.first = *maxY;
                vertexInFin.second = *minX;
                vertex.push_back(vertexInFin);
            } //terzo 

            tmp.first = *maxY;
            tmp.second = *maxX;
            if(find(vertex.begin(), vertex.end(), tmp) == vertex.end())
            {
                vertexInFin.first = *maxY;
                vertexInFin.second = *maxX;
                vertex.push_back(vertexInFin);
            } //quarto
            */
            bossInside = isPointInPath(vertex, bossX, bossY); // OK
            int bossUpDown = -1;
            int bossLeftRight = -1;
            if((boss->getX()-200)/15 < ((colsMax + colsMin)/2))
                bossLeftRight = 0; //sinistra
            else if((boss->getX()-200)/15 >= ((colsMax + colsMin)/2))
                bossLeftRight = 1; //destra
            if(boss->getY()/15 < ((rowsMax + rowsMin)/2))
                bossUpDown = 0; //sopra
            else if(boss->getY()/15 >= ((rowsMax + rowsMin)/2))
                bossUpDown = 1;
            cout<<bossInside<<endl;
            if(*minY == *maxY)
            {
                if(bossUpDown == 0 && player->getPosUpDown() == 0)
                {
                    if(player->getY() < boss->getY())
                    {
                        medioY = *minY - 1;
                        medioX = *minX + 1;
                    }
                    else
                    {
                        medioY = *maxY + 1;
                        medioX = *minX + 1;
                    }
                }
                else if(bossUpDown == 0 && player->getPosUpDown() == 1)
                {
                    medioY = *minY + 1;
                    medioX = *minX + 1;
                }
                else if(bossUpDown == 1 && player->getPosUpDown() == 0)
                {
                    medioY = *minY - 1;
                    medioX = *minX + 1;
                }
                else
                {
                    if(player->getY() < boss->getY())
                    {
                        medioY = *minY - 1;
                        medioX = *minX + 1;
                    }
                    else
                    {
                        medioY = *maxY + 1;
                        medioX = *minX + 1;
                    }
                }
            }
            else if(*minX == *maxX)
            {
                if(bossLeftRight == 0 && player->getPosLeftRight() == 0)
                {
                    if(player->getX() < boss->getX())
                    {
                        medioY = *minY + 1;
                        medioX = *minX - 1;
                    }
                    else
                    {
                        medioY = *maxY + 1;
                        medioX = *minX + 1;
                    }
                }
                else if(bossLeftRight == 0 && player->getPosLeftRight() == 1)
                {
                    medioY = *minY + 1;
                    medioX = *minX + 1;
                }
                else if(bossLeftRight == 1 && player->getPosLeftRight() == 0)
                {
                    medioY = *minY + 1;
                    medioX = *minX - 1;
                }
                else
                {
                    if(player->getX() < boss->getX())
                    {
                        medioY = *minY + 1;
                        medioX = *minX - 1;
                    }
                    else
                    {
                        medioY = *maxY + 1;
                        medioX = *minX + 1;
                    }
                }
                
            }
            else
            {
                for(int i = rowsMin; i < rowsMax; i++)
                {
                    bool found = false;
                    for(int j = colsMin; j < colsMax; j++)
                    {
                        bool uguale = false;
                        for(int p = 0; p < player->getPassiY().size(); p++)
                        {
                            if(player->getPassiY()[p] == i && player->getPassiX()[p] == j)
                            {
                                //cout<<"ciao"<<endl;
                                uguale = true;
                                break;
                            }
                        }
                        if(!uguale && logic_map[i][j] != 7 && logic_map[i][j] != 1)
                        {
                            bool ctrl = true;
                            //floodFillControllo(i, j, -2, -1, ctrl);
                            clearMap();
                            bool x = isPointInPath(vertex, j, i);
                            //cout<<"AAAAAA"<<endl;
                            if(((x && !bossInside) || (!x && bossInside)) && ctrl)
                            {
                                floodFillControllo(i, j, -2, -1, ctrl);

                                //cout<<i<<"asaaaaa "<<j<<endl;
                                medioX = j;
                                medioY = i;
                                cout<<ctrl<<" "<<medioY<<" "<<medioX<<" "<<endl;
                                if(ctrl)
                                    found = true;
                                //break;
                            }
                        }
                        
                    }
                    if(found)
                        break;
                }
            }
            /*if(bossInside && isPointInPath(vertex, *minY + 1, (*minX + *maxX) / 2) == false) //NON OK GLI IF
            {

                medioY = *minY + 1;
                medioX = (*minX + *maxX) / 2; 
            }
            else if(!bossInside && isPointInPath(vertex, *minY + 1, (*minX + *maxX) / 2))
            {
                medioY = *minY + 1;
                medioX = (*minX + *maxX) / 2; 
            }
            else if(bossInside && isPointInPath(vertex, *minY + 1, ((*minX + *maxX) / 2) + 1) == false)
            {
                medioY = *minY + 1;
                medioX = ((*minX + *maxX) / 2) + 1; 
            }
            else if(!bossInside && isPointInPath(vertex, *minY + 1, ((*minX + *maxX) / 2) + 1))
            {
                medioY = *minY + 1;
                medioX = ((*minX + *maxX) / 2) + 1; 
            }
            else if(bossInside && isPointInPath(vertex, *minY + 1, ((*minX + *maxX) / 2) - 1) == false)
            {
                medioY = *minY + 1;
                medioX = ((*minX + *maxX) / 2) - 1; 
            }
            else if(!bossInside && isPointInPath(vertex, *minY + 1, ((*minX + *maxX) / 2) - 1))
            {
                medioY = *minY + 1;
                medioX = ((*minX + *maxX) / 2) - 1; 
            }
            /*else if(isPointInPath(vertex, *minY - 1, ((*minX + *maxX) / 2) - 1))
            {
                medioY = *minY + 1;
                medioX = ((*minX + *maxX) / 2) - 1; 
            }
            else if(isPointInPath(vertex, *minY - 1, ((*minX + *maxX) / 2) + 1))
            {
                medioY = *minY - 1;
                medioX = ((*minX + *maxX) / 2) + 1; 
            }
            else if(isPointInPath(vertex, *minY - 1, ((*minX + *maxX) / 2)))
            {
                medioY = *minY - 1;
                medioX = ((*minX + *maxX) / 2); 
            }
            else if(isPointInPath(vertex, *minY + 1, ((*minX + *maxX) / 2)))
            {
                medioY = *minY + 1;
                medioX = ((*minX + *maxX) / 2); 
            }*/
            //isPointInPath(player->getPassiY(), player->getPassiX(), *minY + 1, (*minX + *maxX) / 2, medioY, medioX);
            //medioY = (player->getPassiY()[0] + player->getPassiY()[player->getPassiY().size()-1]) / 2;
            //medioX = (player->getPassiX()[0] + player->getPassiX()[player->getPassiX().size()-1]) / 2;
            
            //for(int i = 0; i < vertex.size(); i++)
                //cout<<vertex[i].first<<" "<<vertex[i].second<<endl;
            //cout<<endl;
            //cout<<medioY<<" "<<medioX<<endl;

            floodFill(medioY, medioX, 7, -1);
            
            /*switch(player->getPos())
            {
                case 0:floodFill((*minY)+1,(*minX),7,-1); break;
                case 1:floodFill((*minY),(*minX)+1,7,-1); break;
                case 2:floodFill((*minY)+1,(*maxX),7,-1); break;
                case 3:floodFill((*maxY),(*minX)+1,7,-1); break;
            }*/
        
            if(sostituisci)
            {

                
                for(int i = rowsMin; i < rowsMax; i++)
                {
                    for(int j = colsMin; j < colsMax; j++)
                    {
                        if(logic_map[i][j] == -1)
                            logic_map[i][j] = 1;
                    }
                }
                player->svuotaPassi();
                cont = 0;
                comodo = true;
                //cout<<rowsMin<<" "<<rowsMax<<" "<<colsMin<<" "<<colsMax<<endl;
               	updateRows_Cols();
                //cout<<rowsMin<<" "<<rowsMax<<" "<<colsMin<<" "<<colsMax<<endl<<endl;
                //clearMap();

            }
        }
        for(int i = 0; i < player->getSizePassi(); i++)
        {
            for(int j = 0; j < player->getSizePassi(); j++){}
                //cout<<player->getPassiY()[i]<<" "<<player->getPassiX()[j]<<" "<<endl;                    
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
    //player->aggiungiPassiX((player->getX() - 200) / 15);
    //player->aggiungiPassiY((player->getY()) / 15);
    //cout<<(player->getY() / 15);
    //cout<<" "<<((player->getX() - 200) / 15)<<endl;
    x = (player->getX() - 200 + x) / 15;
    y = (player->getY() + y) / 15;
    /*cout<<(player->getY() / 15);
    cout<<" "<<((player->getX() - 200) / 15)<<endl;
    cout<<y<<" "<<x<<endl;*/
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
            rowsMin = i - 1;
            rigaMin = false;
        }
    }
    for(int i = colsMin; i < colsMax; i++)
    {
        bool colonnaNonMinima = true;
        for(int j = rowsMin; j < rowsMax; j++)
        {
            if(logic_map[j][i] == 0)
                colonnaNonMinima = false;
        }
        if( !colonnaNonMinima  && colonnaMin)
        {
            colsMin = i - 1;
            colonnaMin = false;
        }
    }
    /*for(int i = (rowsMax-1); i >= rowsMin; i--)
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
    }*/
}
void GameHandler::directionPlayer()
{
    if((player->getX()-200)/15 < ((colsMax + colsMin)/2))
        player->setPosLeftRight(0); //sinistra
    else if((player->getX()-200)/15 >= ((colsMax + colsMin)/2))
        player->setPosLeftRight(1); //destra
    if(player->getY()/15 < ((rowsMax + rowsMin)/2))
        player->setPosUpDown(0); //sopra
    else if(player->getY()/15 >= ((rowsMax + rowsMin)/2))
        player->setPosUpDown(1); //sotto
}
void GameHandler::clearMap()
{
    for(int i = rowsMin; i < rowsMax; i++)
    {
        for(int j = colsMin; j < colsMax; j++)
        {
            if(logic_map[i][j] == -2)
                logic_map[i][j] = 0;
        }
    }
    /*if(player->getLeft())
    {
        for(int i = rowsMin; i < rowsMax; i++)
        {
            bool clear = false;
            for(int j = colsMin; j < colsMax-1; j++)
            {
                if(logic_map[i][j] == 1)
                {
                    clear = true;
                }
                if(logic_map[i][j] == 0)
                {
                    break;
                }
                if(logic_map[i][j] == 7 && clear)
                {
                    logic_map[i][j] = 0;
                }

            }
        }
    }
    else
    {
        for(int i = rowsMin; i < rowsMax; i++)
        {
            bool clear = false;
            for(int j = colsMax - 1; j >= colsMin; j--)
            {
                if(logic_map[i][j] == 1)
                {
                    clear = true;
                }
                if(logic_map[i][j] == 0)
                {
                    break;
                }
                if(logic_map[i][j] == 7 && clear)
                {
                    logic_map[i][j] = 0;
                }

            }
        }
    }*/
}
void GameHandler:: floodFill(int x,int y,int fill_color,int boundary_color)
{
    if(logic_map[x][y] != fill_color && logic_map[x][y] != boundary_color)
    {
        logic_map[x][y] = fill_color;
        if(x + 1 < rowsMax)
            floodFill(x+1,y,fill_color,boundary_color);
        if(y + 1 < colsMax)
            floodFill(x,y+1,fill_color,boundary_color);
        if(x - 1 >= rowsMin)
            floodFill(x-1,y,fill_color,boundary_color);
        if(y - 1 >= colsMin)
            floodFill(x,y-1,fill_color,boundary_color);
        /*if(x + 1 < rowsMax && y + 1 < colsMax)
            floodFill(x+1,y+1,fill_color,boundary_color);
        if(x + 1 < rowsMax && y - 1 >= colsMin)
            floodFill(x+1,y-1,fill_color,boundary_color);
        if(x - 1 >= rowsMin && y + 1 < colsMax)
            floodFill(x-1,y+1,fill_color,boundary_color);
        if(x - 1 >= rowsMin && y - 1 >= colsMin)
            floodFill(x-1,y-1,fill_color,boundary_color);*/
    }
}
void GameHandler:: floodFillControllo(int x,int y,int fill_color,int boundary_color, bool &controllo)
{
    if(logic_map[x][y] != 4 && logic_map[x][y] != 1 && logic_map[x][y] != boundary_color && controllo
     && logic_map[x][y] != fill_color)
    {
        if(logic_map[x][y] == 3)
        {
            controllo = false;
            return;
        }
        logic_map[x][y] = fill_color;
        if(x + 1 < rowsMax)
            floodFillControllo(x+1,y,fill_color,boundary_color, controllo);
        if(y + 1 < colsMax)
            floodFillControllo(x,y+1,fill_color,boundary_color, controllo);
        if(x - 1 >= rowsMin)
            floodFillControllo(x-1,y,fill_color,boundary_color, controllo);
        if(y - 1 >= colsMin)
            floodFillControllo(x,y-1,fill_color,boundary_color, controllo);
    }
}
bool GameHandler::isPointInPath(vector< pair<int,int> > vertex, int x, int y)
{
    int i = 0, j = vertex.size() - 1;
    bool trovatoLeft = false;
    bool trovatoRight = false;
    bool inside = false;
    for(i; i < vertex.size(); i++)
    {
        int xi = vertex[i].second, yi = vertex[i].first;
        int xj = vertex[j].second, yj = vertex[j].first;
        /*bool intersect = ((yi > y) != (yj > y))
            && (x < (xj - xi) * (y - yi) / (yj - yi) + xi);*/
        bool intersect = ((xi > x) != (xj > x))
            && (y < (yj - yi) * (x - xi) / (xj - xi) + yi);
        if (intersect) inside = !inside;

        /*if(((vertex[i].second > x) != (vertex[j].second > x)) && (y < vertex[i].first + (vertex[j].first - vertex[i].first)
         * (x - vertex[i].second) / (vertex[j].second - vertex[i].second))) //IL BOSS LO TROVA
        {
            return true;
            //break;        
        }*/
        /*if(((vertex[i].second <= x) && ( x < vertex[j].second)) || ((vertex[j].second <= x) && ( x < vertex[i].second)))
        {
            if(y < (vertex[j].first - vertex[i].first) * (x - vertex[i].second) / (vertex[j].second - vertex[i].second) + vertex[i].first)
            {
                trovatoRight = true;
                if(trovatoLeft)
                    return true;
            }
            else
            {
                trovatoLeft = true;
                if(trovatoRight)
                    return true;
            }
            
        }*/
        /*if(((vertex[i].first <= y) && ( y < vertex[j].first)) || ((vertex[j].first <= y) && ( y < vertex[i].first)))
        {
            if(x < (vertex[j].second - vertex[i].second) * (y - vertex[i].first) / (vertex[j].first - vertex[i].first) + vertex[i].second)
            {
                trovatoRight = true;
                if(trovatoLeft)
                    return true;
            }
            else
            {
                trovatoLeft = true;
                if(trovatoRight)
                    return true;
            }
            
        }*/
        
        j = i;
    }
    //return trovatoLeft && trovatoRight;
    //return false;
    return inside;
}