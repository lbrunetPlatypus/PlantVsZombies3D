#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "BoardSquare.h"
#include <vector>
#include "Position.h"
#include "GameObject.h"
#include "Sun.h"
#include "Bullet.h"
#include <ctime>
#include "House.h"

class Gameboard {
    private :
    std::vector<Sun> sunList;
    std::vector<Zombie*> zombiesList;
    std::vector<BoardSquare> squaresList;
    std::vector<Bullet> bulletsList;
	int sizeX;
	int sizeZ;
	House house;
    
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
	bool addPlant(Plant* object, int squareId);
    void addBullet(Bullet bullet);
    BoardSquare getSquare(Position position);
	void checkSunHoveringStatus(int x, int y);
	void UpdateSunScreenCoordinate();
	int selectSun();
	int checkSquareHoveringStatus(int x, int y);
	void UpdateSquareScreenCoordinate();
	void setHouse(House house);
    

    void draw(GLuint texture[], float animPos, float plantAnimPos);
	void UpdateZombies();
	void UpdatePlants();
    void UpdateBullets();
    void UpdateSuns();
    bool isGameover();
};

#endif