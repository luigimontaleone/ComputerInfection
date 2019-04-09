#include "../Header/Map.h"

Map::Map(){}
Map::Map(int rowsMin, int rowsMax, int colsMin, int colsMax, char* bgBW, char* bg, char* b): 
rowsMin(rowsMin), rowsMax(rowsMax), colsMin(colsMin), colsMax(colsMax)
{
    saturation = al_load_bitmap("../Images/prova.png");
    //al_draw_tinted_bitmap(saturation, al_map_rgba_f(1, 1, 1, 0.5), 0, 0, 0);
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
    background = al_load_bitmap(bg);
    if (!background)
    {
        cout<<"failed background";
        return;
    }

}

Map::~Map()
{
    al_destroy_bitmap(background);
    al_destroy_bitmap(background_bw);
    al_destroy_bitmap(border);
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
            if(logic_map[i][j] == 1)
                al_draw_bitmap(border, (j * 15) + 200, (i * 15) , 0);
        }
    }
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
void Map::load_map(string path)
{
    ifstream map(path);
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
int Map::getRowsMax() const { return rowsMax; }
int Map::getRowsMin() const { return rowsMin; }
int Map::getColsMax() const { return colsMax; }
int Map::getColsMin() const { return colsMin; }
int Map::getMaximumCols() const { return maximumCols;}
int Map::getMaximumRows() const { return maximumRows;}