#ifndef PLANT_H
#define PLANT_H
#include "GameObject.h"
#include <string>
class Plant : public GameObject{
    private :
    int hp;
    int coolDown;
    int coolDownState;
    
    public :
    Plant();
    Plant(int cooldown);
    Plant(int cooldown, int hp);
    int getHp();
    void setHp(int hp);
    int getCooldown();
    void setCooldown(int cooldown);
    int getCooldownState();
    void setCooldownState(int cooldownstate);
	bool ApplyDamages(int nbDamages);
    virtual std::string getType();



};
#endif
