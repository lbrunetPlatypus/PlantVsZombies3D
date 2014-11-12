#ifndef PEASHOOTER_H
#define PEASHOOTER_H
#include "Plant.h"
#include "Bullet.h"
class PeaShooter : private Plant{
    private :
    int attackPoint;
    
    public :
    PeaShooter();
    PeaShooter(int attackPoint);
    int getAttackPoint();
    void setAttackPoint(int ap);
    void detectZombie();
    Bullet shoot();
};
#endif