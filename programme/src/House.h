#ifndef HOUSE_H
#define HOUSE_H
#include "GameObject.h"
class House : private GameObject{
    
    private :
    
    public :
		House();
    void detectZombie();
	void draw(GLuint texture[], int length, int width, int height);
};
#endif