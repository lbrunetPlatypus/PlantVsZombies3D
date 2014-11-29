#ifndef PEASHOOTER_H
#define PEASHOOTER_H
#include "Plant.h"
#include <string>
#include "Bullet.h"
class PeaShooter : public Plant{
    private :
    int attackPoint;
    int mouthRadius = 15;
    float mouthLength = 0;
    int angle = 0;
    
    public :
    PeaShooter();
    PeaShooter(int attackPoint);
    int getAttackPoint();
    void setAttackPoint(int ap);
    void detectZombie();
    std::string getType();
	void draw(GLuint texture[], float plantAnimPos);
    void animation();
    Bullet shoot();
};
#endif