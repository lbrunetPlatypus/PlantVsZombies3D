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
    std::vector<Zombie*> zombiesList;
    std::vector<BoardSquare> squaresList;
	int sizeX;
	int sizeZ;
    
    public :
	Gameboard();
	Gameboard(int sizeX,int sizeZ);
    std::vector<BoardSquare> getSquaresList();
    std::vector<Sun> getSunList();
    std::vector<Zombie*> getZombiesList();
    int getSizeX();
    int getSizeZ();
    void zombieSpawn(Zombie &zombie);
    void produceSun(Position position);
	void addObject(GameObject* object, int squareId);
	void deleteObject(int squareID);
    BoardSquare getSquare(Position position);
	void checkHoveringStatus(int x, int y);
	void UpdateScreenCoordinate();
    void draw();
};

#endif