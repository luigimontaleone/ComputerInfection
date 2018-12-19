#include "../Header/GameHandler.h"

GameHandler::GameHandler(): width(830), height(630), FPS(60)
{
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
    read_map(true);
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
    /*ALLEGRO_TIMEOUT timeout;
    al_init_timeout(&timeout, 0.06);*/
    al_start_timer(timer);

    while(1)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        printBG();
        movePlayer(ev);
        boss->moveEnemy();
        if (redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;
            
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }
        //cout<<player->getX()<<" "<<player->getY()<<endl;

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
void GameHandler::read_map(bool create)
{
    bool create2=create;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {

            if (logic_map[i][j] == 3 && create)
            {
                boss = new Enemy(j * 15 + 200, i * 15 , "../Images/enemy.png", true);
                create = false;
            }
            else if (logic_map[i][j] == 1 && create2)
            {
                player = new Player(j * 15 + 200, i * 15, "../Images/pc.png");
                create2 = false;
            }

            /*else
            {
                if (logic_map[i][j] == 3)
                {
                    boss->setX(j * 32);
                    boss->setY(i * 32);
                }
                else if(logic_map[i][j] == 1)
                {

                }
            }*/
        }
    }
}
int GameHandler::read_something_from_map(int i, int j)
{
    return logic_map[i][j];
}
void GameHandler::movePlayer(ALLEGRO_EVENT ev)
{
    switch(ev.keyboard.keycode)
    {
        case ALLEGRO_KEY_UP:
            if(collisionPlayer(player->getX(), player->getY() - player->getSpeed()))
                player->moveUp();
            break;
        case ALLEGRO_KEY_DOWN:
            if(collisionPlayer(player->getX(), player->getY() + player->getSpeed()))
                player->moveDown();
            break;
        case ALLEGRO_KEY_RIGHT:
            if(collisionPlayer(player->getX() + player->getSpeed(), player->getY()))
                player->moveRight();
            break;
        case ALLEGRO_KEY_LEFT:
            if(collisionPlayer(player->getX() - player->getSpeed(), player->getY()))
                player->moveLeft();
            break;
        case ALLEGRO_KEY_SPACE:
            break;
        default:
            break;
    }
    player->print();
}
bool GameHandler::collisionPlayer(int x, int y)
{    
    if (x < 200 || y < 0 || x > width - player->getSize() || y > height - player->getSize())
        return false;

    x = (x - 200) / 15;
    y = y / 15;
    //x--;
    //y--;


    cout<<"x: "<<x<<" y:"<<y<<endl;
            if(read_something_from_map(y, x) != 1)
                return false;
    return true;
}
