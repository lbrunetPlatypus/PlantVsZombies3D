#ifndef SUN_H
#define SUN_H
#include "GameObject.h"
#include "Position.h"

class Sun : public GameObject{
    private :
    int despawn;
	float screenCoordX;
	float screenCoordY;
	bool isHovered;
    
    public :
    Sun();
    int getDespawn();
    void update();
    void draw();
	float getScreenCoordX();
	float getScreenCoordY();
	void setScreencoordX(float _screenCoordX);
	void setScreencoordY(float _screenCoordY);
	bool getIsHovered();
	void setIsHovered(bool status);
	
};
#endif