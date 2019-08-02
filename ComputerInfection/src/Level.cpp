#include "../Header/Level.h"

//costruttore della classe Level, setta tutte le variabili
Level::Level(ALLEGRO_FONT * f, int sW, int sH): screenWidth(sW), screenHeight(sH)
{
    numLevel = 1;
    font = f;
    setLevels();
}

string Level::front() const
{
    return levels.front();
}

void Level::pop_front()
{
    levels.pop_front();
}

bool Level::empty() const
{
    return levels.empty();
}

//metodo che stampa a schermo il numero del livello che si andrà a giocare
void Level::newLevel()
{
    string stage = "STAGE "+to_string(numLevel);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(font, al_map_rgb(255,0,0), screenWidth/2 - 70, screenHeight/2 - 100, 0, stage.c_str());
    al_flip_display();
    al_rest(3);
    numLevel++;
}

//metodo che carica dalla cartella maps i due file .txt rappresentanti le mappe di gioco
void Level::setLevels()
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("../maps")) != NULL)
    {
        while ((ent = readdir (dir)) != NULL)
        {
            if(*ent->d_name != '.')
            {
                levels.push_back(ent->d_name);
            }
            
        }
        closedir(dir);
    } 
    else
    {
        cerr<<"ERRORE apertura cartella";
    }
    levels.sort();
}
