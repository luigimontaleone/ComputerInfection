#include "../Header/Movement.h"

//costruttore della classe Movement, crea un oggetto di tipo CollisionHandler
Movement::Movement()
{
    collisionHandler = new CollisionHandler();
}

//distruttore della classe Movement, distrugge l'area di memoria puntata da collisionHandler
Movement::~Movement()
{
    delete collisionHandler;
}