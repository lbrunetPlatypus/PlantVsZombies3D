#ifndef PEASHOOTER_H
#define PEASHOOTER_H
#include "GameObject.h"
class PeaShooter : private Plant{
    private :
    int attackPoint;
    
    public :
    detectZombie();
    shootAt(Position position);
};
#endif