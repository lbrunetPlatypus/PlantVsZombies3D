#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "BoardSquare.h"
#include <vector>
#include "Position.h"
#include "GameObject.h"
#include "Sun.h"
#include <ctime>

class Gameboard {
    private :
    std::vector<BoardSquare> squaresList;
	int sizeX;
	int sizeZ;
    
    public :
	Gameboard();
	Gameboard(int sizeX,int sizeZ);
    std::vector<BoardSquare> getSquaresList();
    void produceSun();
	void addObject(GameObject* object, int squareId);
	void deleteObject(int squareID);
	void checkHoveringStatus(int x, int y);
	void UpdateScreenCoordinate();
};

#endif