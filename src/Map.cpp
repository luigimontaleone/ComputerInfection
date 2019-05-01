#include "../Header/Map.h"
#include <dirent.h>

Map::Map(){}

Map::Map(int rowsMin, int rowsMax, int colsMin, int colsMax, char* bgBW, char* b): 
rowsMin(rowsMin), rowsMax(rowsMax), colsMin(colsMin), colsMax(colsMax)
{
    saturation = al_load_bitmap("../Images/prova.png");
    border = al_load_bitmap(b);
    if (!border)
    {
        cout<<"failed border bitmap";
        return;
    }
    background_bw = al_load_bitmap(bgBW);
    if (!background_bw)
    {
        cout<<"failed background bw";
        return;
    }

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("/home/simone/Scrivania/ComputerInfection/maps")) != NULL)
    {
        while ((ent = readdir (dir)) != NULL)
        {
            if(*ent->d_name != '.')
            {
                levels.push(ent->d_name);
                cout<<ent->d_name<<endl;
            }
            
        }
        closedir(dir);
    } 
    else
    {
        cerr<<"ERRORE apertura cartella";
    }
    load_map();
    //levels.push("/home/simone/Scrivania/ComputerInfection/maps/map1.txt");
    //levels.push("/home/simone/Scrivania/ComputerInfection/maps/map2.txt");
}

Map::~Map()
{
    al_destroy_bitmap(background_bw);
    al_destroy_bitmap(border);
    al_destroy_bitmap(saturation);
    background_bw = nullptr;
    border = nullptr;
    saturation = nullptr;
}

void Map::printBG() const
{
    al_draw_bitmap(background_bw, 200, 0, 0);
}

void Map::printBorder() const
{
    for(int i = rowsMin; i < rowsMax; i++)
    {
        for(int j = colsMin; j < colsMax; j++)
        {
            if(logic_map[i][j] == 1 || logic_map[i][j] == -1)
                al_draw_bitmap(border, (j * 15) + 200, (i * 15) , 0);
        }
    }
}

void Map::printSaturation() const
{
    for(int i = 0; i < 40; i++)
    {
        for(int j = 0; j < 40; j++)
        {
            if(logic_map[i][j] == 7)
            {
                al_draw_tinted_bitmap(saturation, al_map_rgba_f(1, 0, 0, 0.1), (j * 15) + 200, i * 15, 0);
            }
        }
    }
}

int Map::readFromMap(int i, int j) const
{
    return logic_map[i][j];
}

void Map::writeOnMap(int i, int j, int value)
{
    logic_map[i][j] = value;
}

void Map::updateRows_Cols()
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
        if(!rigaNonMinima  && rigaMin)
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
        if(!colonnaNonMinima  && colonnaMin)
        {
            colsMin = i - 1;
            colonnaMin = false;
        }
    }
    
}

void Map::clearMap()
{
    for(int i = rowsMin; i < rowsMax; i++)
    {
        for(int j = colsMin; j < colsMax; j++)
        {
            if(logic_map[i][j] == -2)
                logic_map[i][j] = 0;
        }
    }
}
bool Map::load_map()
{
    percent = 0.0;
    contEnemies = 0;
    contSeven = 0;
    if(levels.empty())
    {
        return true;
    }
    ifstream map("../maps/" + levels.front());
    levels.pop();
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
    return false;
}
int Map::getRowsMax() const { return rowsMax; }
int Map::getRowsMin() const { return rowsMin; }
int Map::getColsMax() const { return colsMax; }
int Map::getColsMin() const { return colsMin; }
int Map::getMaximumCols() const { return maximumCols; }
int Map::getMaximumRows() const { return maximumRows; }
int Map::getPercent() const { return percent; }
int Map::getContSeven() const { return contSeven; }
int Map::getContEnemies() const { return contEnemies; }
void Map::setContEnemies(int n)
{
    contEnemies = n;
}
void Map::updatePercent()
{
    int contEnemies = 0;
    contSeven = 0;
    for(int i = 0; i < maximumRows; i++)
        for(int j = 0; j < maximumCols; j++)
            if(logic_map[i][j] == 7)
                contSeven++;
            else if(logic_map[i][j] == 4)
                contEnemies++;
    percent = ((contSeven * 100) / (maximumCols * maximumRows));
} 