#ifndef SUNPLANT_H
#define SUNPLANT_H
#include "Plant.h"
class SunPlant : private Plant{
    private :
    
    public :
    SunPlant();
    SunPlant(int cooldown);
    SunPlant(int cooldown, int hp);
    void produceSun();
};
#endif