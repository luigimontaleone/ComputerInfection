#include "../Header/Map.h"

Map::Map(){}

Map::Map(int rowsMin, int rowsMax, int colsMin, int colsMax, string bgBW, string b, string path): 
rowsMin(rowsMin), rowsMax(rowsMax), colsMin(colsMin), colsMax(colsMax)
{
    saturation = al_load_bitmap("../Images/saturazione.png");
    border = al_load_bitmap(b.c_str());
    if (!border)
    {
        cout<<"failed border bitmap";
        return;
    }
    background_bw = al_load_bitmap(bgBW.c_str());
    if (!background_bw)
    {
        cout<<"failed background bw";
        return;
    }
    load_map(path);

    contEnemies = 0;
    contSeven = 0;
    percent = 0.0;
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

/*Stampa l'immagine di sfondo */
void Map::printBG() const
{
    al_draw_bitmap(background_bw, 200, 0, 0);
}

/*Stampa i bordi della mappa */
void Map::printBorder() const
{
    for(int i = rowsMin; i < rowsMax; i++)
    {
        for(int j = colsMin; j < colsMax; j++)
        {
            if(logic_map[i][j] == 1 || logic_map[i][j] == -1)
                al_draw_bitmap(border, (j * 15) + 200, (i * 15), 0);
        }
    }
}

/*Stampa le parti della mappa già "tagliate" */
void Map::printSaturation() const
{
    for(int i = 0; i < maximumRows; i++)
    {
        for(int j = 0; j < maximumCols; j++)
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

/*Se la mappa disponibile è stata tagliata, gli indici (minimi e massimi) delle righe e colonne cambia*/
void Map::updateRows_Cols()
{
    bool rigaMin = true;
    bool colonnaMin = true;

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

/*Metodo di utilità per il controllo della zona del "floodfillcontrollo" che "sporca" la mappa
con "-2", questo metodo la "pulisce" */
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

/*Metodo per caricare la mappa a partire da un file txt */
void Map::load_map(string path)
{
    ifstream map("../maps/" + path);
    
    char ch;
    int c;
    int i = 0;
    int j = 0;

    while(!map.eof())
    {
        map >> logic_map[i][j];
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
int Map::getMaximumCols() const { return maximumCols; }
int Map::getMaximumRows() const { return maximumRows; }
int Map::getPercent() const { return percent; }
int Map::getContSeven() const { return contSeven; }
int Map::getContEnemies() const { return contEnemies; }

void Map::setContEnemies(int n)
{
    contEnemies = n;
}

/*Aggiorna la percentuale di completamento in base ai "7" che trova nella mappa e aggiorna
anche il contatore dei nemici ancora in vita */
void Map::updatePercent()
{
    contEnemies = 0;
    contSeven = 0;

    for(int i = 0; i < maximumRows; i++)
        for(int j = 0; j < maximumCols; j++)
            if(logic_map[i][j] == 7)
                contSeven++;
            else if(logic_map[i][j] == 4)
                contEnemies++;

    percent = ((contSeven * 100) / (maximumCols * maximumRows));
} 