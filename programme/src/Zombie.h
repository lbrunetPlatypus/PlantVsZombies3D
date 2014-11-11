#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "GameObject.h"

class Zombie : private GameObject{
    private :
    int hp;
    int attackPoint;
    int speed;
    
    public :
    bool detectTarget();//detect if something is just in front of the zombie
    void move();
    void nibble();
    bool takeDamages();//say if the zombie die or not?
};
#endif