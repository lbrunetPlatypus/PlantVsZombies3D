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
    //GameObject* object;
    Plant* plant;
    vector<Zombie*> zombieLists;
    Sun sun;
	int id;
	int x;
	int z;
	int screenCoordX;
	int screenCoordY;
	bool isHovered;

    public :
        const static int size = 100;

		BoardSquare();
		BoardSquare(int x, int z,int id);

		//void setObject(GameObject* object);
        void setPlant(Plant* _plant);
        void setSun(Sun* _sun);
		void setX(int x);
		void setZ(int z);
		void set2DPosition(int x, int z);
		void setId(int id);
		

		int getX();
		int getZ();
		Position get2DPosition();
		//GameObject* getObject();
        Plant* getPlant();
        Sun* getSun();
		int getId();
        void draw();

		float getScreenCoordX();
		float getScreenCoordY();
		void setScreencoordX(float _screenCoordX);
		void setScreencoordY(float _screenCoordY);
		bool getIsHovered();
		void setIsHovered(bool status);
		


};
#endif

