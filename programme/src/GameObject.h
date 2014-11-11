#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Position.h"
class GameObject {
    
    private :
    Position position;
    
    public :
    void setPosition(Position newPosition);
};
#endif