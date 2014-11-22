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
    GameObject* object;
    Plant* plant;
    vector<Zombie*> zombieLists;
    Sun sun;
	int id;
	int x;
	int z;
	bool isHovered;
	Vec3 screenCoordinate;

    public :
        const static int size = 100;

		BoardSquare();
		BoardSquare(int x, int z,int id);

		void setObject(GameObject* object);
        void setPlant(Plant* _plant);
        void setSun(Sun* _sun);
		void setX(int x);
		void setZ(int z);
		void set2DPosition(int x, int z);
		void setId(int id);

		int getX();
		int getZ();
		Position get2DPosition();
		GameObject* getObject();
        Plant* getPlant();
        Sun* getSun();
		int getId();
		Vec3 getScreenCoordinate();
		

		void setHoveringStatus(bool status);
		bool getHoveringStatus();
		


};
#endif

