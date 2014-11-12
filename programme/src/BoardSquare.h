#ifndef BOARDSQUARE_H
#define BOARDSQUARE_H
#include "GameObject.h"

class BoardSquare {
    
    private :
    GameObject object;
	int id;
	int x;
	int z;
    
    public :
		BoardSquare();
		BoardSquare(int x, int z,int id);

		void setObject(GameObject object);
		void setX(int x);
		void setZ(int z);
		void set2DPosition(int x, int z);
		void setId(int id);

		int getX();
		int getZ();
		Position get2DPosition();
		GameObject getObject();
		int getId();

		


};
#endif

