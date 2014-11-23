#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "GameObject.h"
#include "Plant.h"

class Zombie : public GameObject{
    private :
    int hp;
    int attackPoint;
    int speed;
    
    public :
    Zombie();
    int getHp();
    int getAttackPoint();
    int getSpeed();
	bool detectTarget(Plant& plant);//detect if something is just in front of the zombie
    void move();
	void nibble(Plant& plant, int nbDamages);
    bool takeDamages(int nbDamages);//say if the zombie die or not?
    void draw();
};
#endif