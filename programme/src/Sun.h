#ifndef SUN_H
#define SUN_H
#include "GameObject.h"
class Sun : public GameObject{
    private :
    int despawn;
    
    public :
    Sun();
    void draw();
};
#endif