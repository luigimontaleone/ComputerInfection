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
    scaleX = (width / (float) menuWidth);
    scaleY = (height / (float) menuHeight);
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

Menu::~Menu()
{
    al_destroy_display(menuDisplay);
    al_destroy_font(choicesFont);
    al_destroy_font(titleFont);
    al_destroy_timer(timer);
    al_destroy_event_queue(menuEventsQueue);
    menuDisplay = nullptr;
    choicesFont = nullptr;
    titleFont = nullptr;
    timer = nullptr;
    menuEventsQueue = nullptr;
}

int Menu::showMenu() const
{
    int mouseX = 0;
    int mouseY = 0;
    int startRectangleX = ((menuWidth / 2) - 100);
    int endRectangleX = (startRectangleX + 200) ;
    int startChoicesY1 = 200 ;
    int endRectangleY1 = (startChoicesY1 + 50);
    int startChoicesY2 = startChoicesY1 + 100 ;
    int endRectangleY2 = (startChoicesY2 + 50);
    int startChoicesY3 = startChoicesY1 + 200;
    int endRectangleY3 = (startChoicesY3 + 50);
    int startChoicesXPlay = (startRectangleX + 50);
    int startChoicesXCredits = (startRectangleX + 25);
    al_register_event_source(menuEventsQueue, al_get_mouse_event_source());
    al_register_event_source(menuEventsQueue, al_get_display_event_source(menuDisplay));
    al_register_event_source(menuEventsQueue, al_get_timer_event_source(timer));
    while(true)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(menuEventsQueue, &event);
        al_draw_text(titleFont, al_map_rgb(255,255,255), sizeTitle, 50, 0, "COMPUTER INFECTION");

        al_draw_rectangle(startRectangleX, startChoicesY1, endRectangleX, endRectangleY1, al_map_rgb(255,0,0),1);
        al_draw_text(choicesFont, al_map_rgb(255,255,255), startChoicesXPlay, startChoicesY1, 0, "PLAY");

        al_draw_rectangle(startRectangleX, startChoicesY2, endRectangleX, endRectangleY2, al_map_rgb(255,0,0),1);
        al_draw_text(choicesFont, al_map_rgb(255,255,255), startChoicesXCredits, startChoicesY2, 0, "CREDITS");

        al_draw_rectangle(startRectangleX, startChoicesY3, endRectangleX, endRectangleY3, al_map_rgb(255,0,0),1);
        al_draw_text(choicesFont, al_map_rgb(255,255,255), startChoicesXPlay, startChoicesY3, 0, "EXIT");
        mouseX = event.mouse.x;
        mouseY = event.mouse.y;
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            if(mouseX >= startRectangleX*scaleX && mouseX <= endRectangleX*scaleX)
            {
                if(mouseY >= startChoicesY1*scaleY && mouseY <= endRectangleY1*scaleY)
                {
                    return Menu::PLAY;
                }
                if(mouseY >= startChoicesY2*scaleY && mouseY <= endRectangleY2*scaleY)
                {
                    return Menu::CREDITS;
                }
                if(mouseY >= startChoicesY3*scaleY && mouseY <= endRectangleY3*scaleY)
                {
                    return Menu::EXIT;
                }
            }
            
        }
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
    }
    return 0;
    
    
}