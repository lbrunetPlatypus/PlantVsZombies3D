#ifndef PLANT_H
#define PLANT_H
#include "GameObject.h"
class Plant : public GameObject{
    private :
    int hp;
    int coolDown;
    
    public :
    Plant();
    Plant(int cooldown);
    Plant(int cooldown, int hp);
    int getHp();
    void setHp(int hp);
    int getCooldown();
    void setCooldown(int cooldown);



};
#endif
