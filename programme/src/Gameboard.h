#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "BoardSquare.h"
#include <vector>
#include "Position.h"
#include "GameObject.h"
#include "Sun.h"
#include "Bullet.h"
#include <ctime>

class Gameboard {
    private :
    std::vector<Sun> sunList;
    std::vector<Zombie*> zombiesList;
    std::vector<BoardSquare> squaresList;
    std::vector<Bullet> bulletsList;
	int sizeX;
	int sizeZ;
    
    public :
	Gameboard();
	Gameboard(int sizeX,int sizeZ);
    std::vector<BoardSquare> getSquaresList();
    std::vector<Sun> getSunList();
    std::vector<Zombie*> getZombiesList();
    std::vector<Bullet> getBulletsList();
    int getSizeX();
    int getSizeZ();
    void zombieSpawn(Zombie &zombie);
    void produceSun(Position position);
    void addSun(Sun sun);
	void addPlant(Plant* object, int squareId);
    void addBullet(Bullet bullet);
	void deleteObject(int squareID);
    BoardSquare getSquare(Position position);
	void checkHoveringStatus(int x, int y);
	void UpdateScreenCoordinate();
    void draw();
	void UpdateZombies();
	void UpdatePlants();
    void UpdateBullets();
};

#endif