#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "GameObject.h"
#include "Plant.h"

class Zombie : public GameObject{
    private :
    int hp;
    int attackPoint;
    int speed;
    int coolDown;
    int coolDownState;
    
    public :
    Zombie();
    int getHp();
    int getAttackPoint();
    int getSpeed();
    int getCooldown();
    int getCooldownState();
    void setCooldown(int _cooldown);
    void setCooldownState(int _cooldownState);
	bool detectTarget(Plant& plant);//detect if something is just in front of the zombie
    void move();
	void nibble(Plant& plant, int nbDamages);
    bool takeDamages(int nbDamages);//say if the zombie die or not?
    void draw();
};
#endif