#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Position.h"
#include "Gameboard.h"

class GameObject {
    
    private :
    Position position;
    static Gameboard gameboard;
    
    public :
    void setPosition(Position newPosition);
	Position getPosition();
};
#endif