#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "BoardSquare.h"
#include <vector>
#include "Position.h"
#include "GameObject.h"
#include <ctime>

class Gameboard {
    private :
    std::vector<BoardSquare> squaresList;
	int sizeX;
	int sizeZ;
    
    public :
	Gameboard();
	Gameboard(int sizeX,int sizeZ);
	void addObject(GameObject object, int squareId);
	void deleteObject(int squareID);
};

#endif