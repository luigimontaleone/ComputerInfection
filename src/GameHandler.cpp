#include "../Header/GameHandler.h"

GameHandler::GameHandler( int displayW, int displayH): FPS(30), pressedSpaceBar(false), redraw(true), lastOne(true),
screenWidth(displayW), screenHeight(displayH)
{
    font = al_load_ttf_font("../Font/score.ttf", 35, 0);
    level = new Level(font, screenWidth, screenHeight);
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);
    map = new Map(0, 40, 0, 40, "../Images/backgroundBW.png", "../Images/board.png", level->front());
    level->pop_front();
    playerMovement = new PlayerMovement();
    enemyMovement = new EnemyMovement();
    initPos();
    map->setContEnemies(enemies.size());
}
void GameHandler::Game()
{
    level->newLevel();
    map->printBG();
    al_register_event_source(event_queue, al_get_display_event_source(al_get_current_display()));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
    ALLEGRO_EVENT_QUEUE *timer_queue;
    timer_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    ALLEGRO_EVENT ev, evPrec, timer;
    ALLEGRO_KEYBOARD_STATE state;
    while(true)//!exit_clause)
    {
        al_wait_for_event(event_queue, &ev);
        if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            break;
        }
        if(ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
        {
            pressedSpaceBar = true;
        }
        al_get_keyboard_state(&state);
            if(al_key_down(&state, ALLEGRO_KEY_SPACE))
                pressedSpaceBar = true;
            else
                pressedSpaceBar = false;
            if(al_key_down(&state, ALLEGRO_KEY_UP))
                evPrec.keyboard.keycode = ALLEGRO_KEY_UP;
            if(al_key_down(&state, ALLEGRO_KEY_DOWN))
                evPrec.keyboard.keycode = ALLEGRO_KEY_DOWN;
            if(al_key_down(&state, ALLEGRO_KEY_RIGHT))
                evPrec.keyboard.keycode = ALLEGRO_KEY_RIGHT;
            if(al_key_down(&state, ALLEGRO_KEY_LEFT))
                evPrec.keyboard.keycode = ALLEGRO_KEY_LEFT;        
        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
            for(int i = 0; i < enemies.size(); i++)
            {
                if(enemies[i]->getAlive())
                {
                    enemyMovement->movement(enemies[i], player, map, pressedSpaceBar); 
                }
            }
            enemyMovement->movement(boss, player, map, pressedSpaceBar);
            if(player->getLives() <= 0)
            {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(font, al_map_rgb(255,0,0), screenWidth/2 - 100, screenHeight/2 - 100, 0, "HAI PERSO");
                al_flip_display();
                al_rest(3);
                //exit_clause = true;
                break;
            }
            if(map->getPercent() >= 75)
            {
                pressedSpaceBar = false;
                for(int i = 0; i < enemies.size(); i++)
                {
                    delete enemies[i];
                }
                enemies.clear();
                delete player;
                delete boss;
                delete map;
                al_flush_event_queue(event_queue);
                if(level->empty())
                {
                    ALLEGRO_COLOR color = al_map_rgb(255,0,0);
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    al_draw_text(font, color, screenWidth/2 - 100, screenHeight/2 - 100, 0, "HAI VINTO");
                    al_flip_display();
                    al_rest(3);
                    break;
                }
                level->newLevel();
                map = new Map(0, 40, 0, 40, "../Images/backgroundBW.png", "../Images/board.png", level->front());
                level->pop_front();
                initPos();
                map->setContEnemies(enemies.size());
            }
            if(pressedSpaceBar)
            {
                player->setCutting(true);
                playerMovement->movement(player, map, evPrec, pressedSpaceBar);   
            }
            else
            {
                player->setCutting(false);
                if(player->getPassiX().empty())
                {
                    playerMovement->movement(player, map, evPrec, pressedSpaceBar);
                }
                else
                {
                    if(lastOne)
                    {
                        player->aggiungiPassiX((player->getX() - 200) / 15);
                        player->aggiungiPassiY((player->getY()) / 15);
                        lastOne = false;
                    }
                    int x_tmp = player->getPassiX()[player->getPassiX().size() - 1 ];
                    int y_tmp = player->getPassiY()[player->getPassiY().size() - 1 ];
                    player->setX((x_tmp * 15) + 200);
                    player->setY(y_tmp * 15);
                    if(player->getPassiX().size() > 1)
                        map->writeOnMap(y_tmp, x_tmp, 0);
                    else
                    {
                        map->writeOnMap(y_tmp, x_tmp, 1);
                        lastOne = true;
                    }
                    player->popBackPassi();
                }
            }         
        }
        else
        {
            
        }
        
        /*DEBUG*/
        if(ev.type == ALLEGRO_EVENT_KEY_UP && ev.keyboard.keycode == ALLEGRO_KEY_H)
        {
            for(int i = 0; i < map->getMaximumRows(); i++)
            {
                for(int j = 0; j < map->getMaximumCols(); j++)
                {
                    cout<<map->readFromMap(i,j);
                }
                cout<<endl;
            }
        }
        /*END DEBUG*/
     

        //if(ev.type == ALLEGRO_EVENT_KEY_UP && ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
          //  pressedSpaceBar = false;
        
        if(ev.type == ALLEGRO_EVENT_KEY_UP)
            evPrec.keyboard.keycode = ALLEGRO_KEY_A; //viene impostato ad un valore "casuale" così 
                                                    // da non continuare a camminare, viene usato come "stop"
        if (redraw && al_is_event_queue_empty(event_queue)) //&& !exit_clause)
        {
            redraw = false;           
            map->printBG();
            map->printBorder();
            map->printSaturation();
            printInfo();
            boss->print();
            for(int i = 0; i < enemies.size(); i++)
            {
                if(enemies[i]->getAlive())
                    enemies[i]->print();
            }
            player->print();
            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
        }
    }
    al_flush_event_queue(event_queue);
}
void GameHandler::initPos()
{
    bool createPlayer = true; //per distinguere il player con il bordo, entrambi hanno codice 1
    for (int i = map->getRowsMin(); i < map->getRowsMax(); i++)
    {
        for (int j = map->getColsMin(); j < map->getColsMax(); j++)
        {

            if (map->readFromMap(i,j) == 3) 
            {
                boss = new Enemy(j * 15 + 200, i * 15 , "../Images/enemy.png", true, 3);
            }
            else if (map->readFromMap(i,j) == 4)
            {
                enemies.push_back(new Enemy(j * 15 + 200, i * 15, "../Images/enemy2.png", false, 3));
            }
            else if (map->readFromMap(i,j) == 1 && createPlayer)
            {
                player = new Player((j * 15 + 200), i * 15, "../Images/pc.png");
                createPlayer = false;
            }
        }
    }
}

void GameHandler::printInfo()
{
    ALLEGRO_COLOR colorFont;
    colorFont = al_map_rgb(255,255,255);
    string lives = "LIVES : " + to_string(player->getLives());
    player->setScore(map->getContSeven() * 5 + ((enemies.size() - map->getContEnemies()) * 50));
    string score = "SCORE : " + to_string(player->getScore());
    string percent = to_string(map->getPercent()) + "%";
    al_draw_text(font, colorFont, 20, 50, 0, lives.c_str());
    al_draw_text(font, colorFont, 5, 100, 0, score.c_str());
    al_draw_text(font, colorFont, 20, 150, 0, percent.c_str());
}
GameHandler::~GameHandler()
{
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_timer(timer);
    //delete player;
    //delete boss;
    //delete map;
    delete level;
    delete playerMovement;
    delete enemyMovement;
    /*for(int i = 0; i < enemies.size(); i++)
    {
        delete enemies[i];
    }*/
    event_queue = nullptr;
    font = nullptr;
    timer = nullptr;
}