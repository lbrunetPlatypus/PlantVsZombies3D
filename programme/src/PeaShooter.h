#ifndef PEASHOOTER_H
#define PEASHOOTER_H
#include "GameObject.h"
class PeaShooter : private Plant{
    private :
    int attackPoint;
    
    public :
    void detectZombie();
    void shootAt(Position position);
};
#endif