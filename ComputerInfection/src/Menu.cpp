#include "../Header/Menu.h"

Menu::Menu(int displayW, int displayH, float scaleX, float scaleY): 
menuWidth(displayW), menuHeight(displayH), scaleX(scaleX), scaleY(scaleY)
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
    
    sizeTitle = 55;
    sizeChoices = 100;
    choicesFont = al_load_ttf_font("../Font/choices.ttf", sizeChoices, 0);
    titleFont = al_load_ttf_font("../Font/title.ttf", sizeTitle, 0); 

    timer = al_create_timer(1.0 / 30);
    al_start_timer(timer);
}

Menu::~Menu()
{
    al_destroy_font(choicesFont);
    al_destroy_font(titleFont);
    al_destroy_timer(timer);
    al_destroy_event_queue(menuEventsQueue);
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
    al_register_event_source(menuEventsQueue, al_get_display_event_source(al_get_current_display()));
    al_register_event_source(menuEventsQueue, al_get_timer_event_source(timer));

    while(true)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(menuEventsQueue, &event);
        al_draw_text(titleFont, al_map_rgb(255,255,255), 10, 50, 0, "COMPUTER INFECTION");

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

void Menu::showCredits() const
{
    int mouseX = 0;
    int mouseY = 0;
    int titleX = 10;
    int titleY = 50;
    int startRectangleX = 10;
    int startRectangleY = 450;
    int endRectangleX = startRectangleX + 100;
    int endRectangleY = startRectangleY + 70;
    bool exit = false;

    al_register_event_source(menuEventsQueue, al_get_mouse_event_source());

    while(!exit)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(menuEventsQueue, &event);

        al_draw_text(titleFont, al_map_rgb(255,255,255), titleX, titleY, 0, "COMPUTER INFECTION");
        al_draw_text(choicesFont, al_map_rgb(255,255,255), titleX, titleY+70, 0, "Game made by");
        al_draw_text(choicesFont, al_map_rgb(255,255,255), titleX, titleY+120, 0, "Simone Mungari");
        al_draw_text(choicesFont, al_map_rgb(255,255,255), titleX, titleY+170, 0, "Luigi Montaleone");
        al_draw_text(choicesFont, al_map_rgb(255,255,255), titleX, titleY+220, 0, "Project for the exam:");
        al_draw_text(choicesFont, al_map_rgb(255,255,255), titleX, titleY+270, 0, "Programmazione ad Oggetti");

        al_draw_rectangle(startRectangleX, startRectangleY, endRectangleX, endRectangleY, al_map_rgb(255,0,0),1);
        al_draw_text(choicesFont, al_map_rgb(255,255,255), startRectangleX+5, startRectangleY+5, 0, "back");
        
        mouseX = event.mouse.x;
        mouseY = event.mouse.y;

        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            if(mouseX >= startRectangleX*scaleX && mouseX <= endRectangleX*scaleX
            && mouseY >= startRectangleY*scaleY && mouseY <= endRectangleY*scaleY)
                exit = true;
                
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
    }
}