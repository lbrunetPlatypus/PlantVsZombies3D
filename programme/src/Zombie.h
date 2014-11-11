#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "GameObject.h"
class Zombie : private GameObject{
    private :
    int hp;
    int attackPoint;
    int speed;
    
    public :
    detectTarget();
    move();
    nibble();
    takeDamages();
};
#endif