#include "Gameboard.h"
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <cmath>


Gameboard::Gameboard(){

}

Gameboard::Gameboard(int _sizeX,int _sizeZ){
	sizeX = _sizeX;
	sizeZ = _sizeZ;
	int id = -1;
	for (int i = 0; i < _sizeX; i++){
		for (int j = 0; j < _sizeZ; j++){
			id++;
			BoardSquare tempSquare = BoardSquare(i, j, id );
			squaresList.push_back(tempSquare);
		}
	}

}

std::vector<BoardSquare> Gameboard::getSquaresList() {
    return squaresList;
}

std::vector<Sun> Gameboard::getSunList(){
    return sunList;
}

std::vector<Zombie*> Gameboard::getZombiesList() {
    return zombiesList;
}

std::vector<Bullet> Gameboard::getBulletsList() {
    return bulletsList;
}

int Gameboard::getSizeX() {
    return sizeX;
}

int Gameboard::getSizeZ() {
    return sizeZ;
}

void Gameboard::zombieSpawn(Zombie &zombie) {
    zombie.setPosition(Position(sizeX*BoardSquare::size, 0, (rand()%4+0.5)*BoardSquare::size));
    zombiesList.push_back(&zombie);
}

void Gameboard::produceSun(Position position) {
    Sun sun;
    BoardSquare square = getSquare(position);
    sun.setPosition(Position((square.getX()+0.5)*BoardSquare::size, 0, (square.getZ()+0.5)*BoardSquare::size+30));
    sunList.push_back(sun);
}

void Gameboard::addSun(Sun sun) {
    if (sun.getPosition().getX() != 0 && sun.getPosition().getZ() != 0) {
        sunList.push_back(sun);
    }
}

void Gameboard::addPlant(Plant* object,int squareId){
	//set object position using the square?
    BoardSquare square = squaresList[squareId];
    object->setPosition(Position((square.getX()+0.5)*BoardSquare::size, 0, (square.getZ()+0.5)*BoardSquare::size));
	squaresList[squareId].setPlant((Plant*)object);
	
}

void Gameboard::addBullet(Bullet bullet) {
    if (bullet.getPosition().getX() != 0 && bullet.getPosition().getZ() != 0) {
        bulletsList.push_back(bullet);
    }
}

BoardSquare Gameboard::getSquare(Position position){
    int i,j;
    i = position.getX()/BoardSquare::size;
    j = position.getZ()/BoardSquare::size;
    
    return getSquaresList().at(sizeZ*i+j);
}

void Gameboard::deleteObject(int squareId){

}

void Gameboard::UpdateScreenCoordinate()
{
	/*GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLdouble winX, winY, winZ;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	for (unsigned i = 0; i<squaresList.size(); i++)
	{
		double mm[16];
		//mult(modelview, joints[i].global_t, mm);

		gluProject((GLdouble)squaresList[i].get2DPosition().getX(), squaresList[i].get2DPosition().getY(), (GLdouble)squaresList[i].get2DPosition().getZ(),
			modelview, projection, viewport,
			&winX, &winY, &winZ);
		squaresList[i].setScreenCoordinateX(winX);
		squaresList[i].setScreenCoordinateY((double)glutGet(GLUT_WINDOW_HEIGHT) - winY) ;
	}*/
	
}

void Gameboard::checkHoveringStatus(int x, int y)//x, y being the mouse position on screen
{
	double distance = 0.0f;
	double minDistance = 1000.0f;
	int hoveredSquare = -1;
	for (unsigned i = 0; i < squaresList.size(); i++)
	{
		squaresList[i].setHoveringStatus(false);
		distance = sqrt((x - squaresList[i].getScreenCoordinate().x)*(x - squaresList[i].getScreenCoordinate().y)
			+ (y - squaresList[i].getScreenCoordinate().y)*(y - squaresList[i].getScreenCoordinate().y));
		if (distance > 50) continue;
		if (distance < minDistance)
		{
			hoveredSquare = i;
			minDistance = distance;
		}
	}
	if (hoveredSquare != -1) squaresList[hoveredSquare].setHoveringStatus(true);
}

void Gameboard::draw() {
    int n = zombiesList.size();
    int o = bulletsList.size();
    
    for (int i=0; i<squaresList.size(); i++) {
        squaresList[i].draw();
        if (squaresList.at(i).getPlant() != nullptr) {
            if ((squaresList.at(i).getPlant())->getHp() > 0) {
                squaresList.at(i).getPlant()->draw();
            }else {
                squaresList.at(i).setPlant(nullptr);
            }
        }
    }
    for (int j=0; j<n; j++) {
        if (zombiesList[j]->takeDamages(0)) {
            zombiesList.erase(zombiesList.begin()+j);
            n--;
        } else {
            zombiesList[j]->draw();            
        }
    }
    
    for (int k=0; k<o; k++) {
        int j=0;
        while (!bulletsList.at(k).checkCollision(*zombiesList.at(j)) && j<n-1 ) {
            j++;
        }
        if (j<n-1 || bulletsList.at(k).getPosition().getX()>sizeX*BoardSquare::size) {
            bulletsList.erase(bulletsList.begin() + k);
            o--;
        }else {
            bulletsList.at(k).draw();
        }
    }
    
    for (int l=0; l<sunList.size(); l++) {
        sunList[l].draw();
    }
}

void Gameboard::UpdateZombies(){
	float line;
	float column;
	bool plantInFront=false;
	//for each zombie
	for (unsigned i = 0; i < zombiesList.size(); i++){
		line = (zombiesList[i]->getPosition().getZ()-50)/(int)100;
		column =floor((zombiesList[i]->getPosition().getX()) / 100);
		if (column == sizeX)
			column = sizeX-1;
		//for plant on the zombies line
		for (int j = line+(column)*sizeZ; j >= line && !plantInFront; j -= sizeZ) {
			
			Plant* tempPlant = squaresList[j].getPlant();
			if (tempPlant != nullptr){
				plantInFront = true;
				if (zombiesList[i]->detectTarget(*tempPlant)){
					zombiesList[i]->nibble(*tempPlant, 3);
				}
				else
				{
					zombiesList[i]->move();
				}
			}
		}
		if (!plantInFront){
			zombiesList[i]->move();
		}
		plantInFront = false;
	}
	
	
	// if(detectTarget)
		//nibbleOnPlant
	//else
		//move
	
}

void Gameboard::UpdatePlants() {
    
    
}

void Gameboard::UpdateBullets() {
    for (int i=0; i<bulletsList.size(); i++) {
        if (bulletsList.at(i).getPosition().getX() != 0 && bulletsList.at(i).getPosition().getZ()!=0) {
            bulletsList.at(i).move();
            
        }
    }
}

const Vec3 operator + (const Vec3& v1, const Vec3& v2){
	return Vec3(v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z);
}
const Vec3 operator * (const Vec3& v1, const double& coeff){
	return Vec3(v1.x*coeff,
		v1.y*coeff,
		v1.z*coeff);
}
const Vec3 operator - (const Vec3& v1, const Vec3& v2){
	return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}
