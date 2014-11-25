#ifndef BOARDSQUARE_H
#define BOARDSQUARE_H
#include "GameObject.h"
#include "Plant.h"
#include "Sun.h"
#include "Zombie.h"
#include <vector>
using namespace std;

class BoardSquare {
    
    private :
    Plant* plant;
	int id;
	int x;
	int z;
	int screenCoordX;
	int screenCoordY;
	bool isHovered;

    public :
        const static int size = 100;

		BoardSquare(int x, int z,int id);

        void setPlant(Plant* _plant);
		void setX(int x);
		void setZ(int z);
		void set2DPosition(int x, int z);
		void setId(int id);

		int getX();
		int getZ();
		Position get2DPosition();
        Plant* getPlant();
		int getId();
        void draw(GLuint texture[]);

		float getScreenCoordX();
		float getScreenCoordY();
		void setScreencoordX(float _screenCoordX);
		void setScreencoordY(float _screenCoordY);
		bool getIsHovered();
		void setIsHovered(bool status);

};
#endif

