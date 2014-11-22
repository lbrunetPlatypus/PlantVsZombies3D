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
    std::vector<Sun> sunList;
    std::vector<BoardSquare> squaresList;
	int sizeX;
	int sizeZ;
    
    public :
	Gameboard();
	Gameboard(int sizeX,int sizeZ);
    std::vector<BoardSquare> getSquaresList();
    std::vector<Sun> getSunList();
    void produceSun(Position position);
	void addObject(GameObject* object, int squareId);
	void deleteObject(int squareID);
    BoardSquare getSquare(Position position);
	void checkHoveringStatus(int x, int y);
	void UpdateScreenCoordinate();
};

#endif