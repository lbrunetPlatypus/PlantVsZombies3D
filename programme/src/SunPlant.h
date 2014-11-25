#ifndef SUNPLANT_H
#define SUNPLANT_H
#include "Plant.h"
#include <string>
#include "Sun.h"
class SunPlant : public Plant{
    private :
    
    public :
    SunPlant();
    SunPlant(int cooldown);
    SunPlant(int cooldown, int hp);
    Sun produceSun();
    std::string getType();
    void draw(GLuint texture[]);
};
#endif