#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "GameObject.h"
#include "Plant.h"

class Zombie : public GameObject{
    private :
    int hp;
    float despawn;
    int attackPoint;
    int speed;
    int coolDown;
    int coolDownState;
    Position armPosition, legPosition, headPosition;
    
    public :
    Zombie();
    int getDespawn();
    int getHp();
    int getAttackPoint();
    int getSpeed();
    int getCooldown();
    int getCooldownState();
    void setCooldown(int _cooldown);
    void setCooldownState(int _cooldownState);
	bool detectTarget(Plant& plant);//detect if something is just in front of the zombie
    void move();
	void nibble(Plant& plant);//attack a plant with attackPoint damage
    bool takeDamages(int nbDamages);//say if the zombie die or not?
    void draw(GLuint texture[], float animPos);
};
#endif