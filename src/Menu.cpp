#include "../Header/Menu.h"

Menu::Menu()
{
    if(!al_install_mouse())
    {
        cout<<"failed to install mouse";
        return;
    }
    menuEventsQueue = al_create_event_queue();
    if(!menuEventsQueue)
    {
        cout<<"failed to create menu events queue";
        return;
    }
    al_get_display_mode(0, &disp_data);
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    initDisplay();
    sizeTitle = 60;
    sizeChoices = 100;
    choicesFont = al_load_ttf_font("../Font/choices.ttf", sizeChoices, 0);
    titleFont = al_load_ttf_font("../Font/title.ttf", sizeTitle, 0);

    
    timer = al_create_timer(1.0 / 30);
    al_start_timer(timer);
}
void Menu::initDisplay()
{
    int width = disp_data.width;
    int height = disp_data.height;
    menuWidth = 960;
    menuHeight = 600;
    float scaleX = (width / (float) menuWidth);
    float scaleY = (height / (float) menuHeight);
    menuDisplay = al_create_display(width, height);
    if(!menuDisplay)
    {
        cout<<"failed to create menu display";
        return;
    }
    al_identity_transform(&trans);
    al_scale_transform(&trans, scaleX, scaleY);
    al_use_transform(&trans);
}
void Menu::closeDisplay()
{
    al_destroy_display(menuDisplay);
}

Menu::~Menu()
{
    //al_destroy_display(menuDisplay);
    //al_destroy_font(choicesFont);
    //al_destroy_font(titleFont);
    //al_destroy_timer(timer);
    al_destroy_event_queue(menuEventsQueue);
    /*menuDisplay = nullptr;
    choicesFont = nullptr;
    titleFont = nullptr;
    timer = nullptr;
    menuEventsQueue = nullptr;*/
}

int Menu::showMenu() const
{
    int mouseX = 0;
    int mouseY = 0;
    int startChoicesX = (menuWidth / 2)-(sizeChoices /2);
    int endChoicesX = startChoicesX + (sizeChoices * 4);
    int startChoicesY = 200;
    int endChoicesY = startChoicesY + sizeChoices;
    al_register_event_source(menuEventsQueue, al_get_mouse_event_source());
    al_register_event_source(menuEventsQueue, al_get_display_event_source(menuDisplay));
    al_register_event_source(menuEventsQueue, al_get_timer_event_source(timer));
    while(true)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(menuEventsQueue, &event);
        al_draw_text(titleFont, al_map_rgb(255,255,255), sizeTitle, 50, 0, "COMPUTER INFECTION");
        al_draw_text(choicesFont, al_map_rgb(255,255,255), startChoicesX, startChoicesY, 0, "PLAY");
        al_draw_text(choicesFont, al_map_rgb(255,255,255), startChoicesX, startChoicesY + 100, 0, "CREDITS");
        al_draw_text(choicesFont, al_map_rgb(255,255,255), startChoicesX, startChoicesY + 200, 0, "EXIT");
            //616 281 play
//616 410 credits
//616 535 exit

//759 293 play
//837 445 credits
//738 572 exit
        mouseX = event.mouse.x;
        mouseY = event.mouse.y;
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            if(mouseX >= 616 && mouseX <= 759)
            {
                if(mouseY >= 281 && mouseY <= 293)
                {
                    return Menu::PLAY;
                }
            }
            if(mouseX >= 616 && mouseX <= 837)
            {
                if(mouseY >= 410 && mouseY <= 445)
                {
                    return Menu::CREDITS;
                }
            }
            if(mouseX >= 616 && mouseX <= 738)
            {
                if(mouseY >= 535 && mouseY <= 572)
                {
                    return Menu::EXIT;
                }
            }
            /*if(mouseX >= startChoicesX && mouseX <= endChoicesX)
            {
                if(mouseY >= startChoicesY && mouseY <= endChoicesY)
                {
                    return Menu::PLAY;
                }
                if(mouseY >= startChoicesY+200 && mouseY <= endChoicesY+200)
                {
                    return Menu::EXIT;
                }
            }
            if(mouseX >= startChoicesX && mouseX <= startChoicesX + (sizeChoices * 7))
            {
                if(mouseY >= startChoicesY+100 && mouseY <= endChoicesY+100)
                {
                    return Menu::CREDITS;
                }
            }*/
        }
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
    }
    return 0;
    
    
}