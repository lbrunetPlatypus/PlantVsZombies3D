#ifndef BULLET_H
#define BULLET_H
#include "GameObject.h"
#include "Zombie.h"
class Bullet : public GameObject{
    
    private :
    
    public :
    void draw();
    void move();
    bool checkCollision(Zombie& zombie);
};
#endif