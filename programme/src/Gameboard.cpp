#include "Gameboard.h"
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "PeaShooter.h"
#include "SunPlant.h"


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
    zombie.setPosition(Position(sizeX*BoardSquare::size, 0, (rand()%5+0.5)*BoardSquare::size));
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
    if (square.getPlant() ==nullptr) {
    object->setPosition(Position((square.getX()+0.5)*BoardSquare::size, 0, (square.getZ()+0.5)*BoardSquare::size));
	squaresList[squareId].setPlant(object);
    }
	
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



void Gameboard::draw() {
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
    for (int j=0; j<zombiesList.size(); j++) {
        if (zombiesList[j]->takeDamages(0)) {
            zombiesList.erase(zombiesList.begin()+j);
        } else {
            zombiesList[j]->draw();            
        }
    }
    
    for (int k=0; k<bulletsList.size(); k++) {
        int j=0;
        while (zombiesList.size()>0 && !bulletsList.at(k).checkCollision(*zombiesList.at(j)) && j<zombiesList.size()-1 ) {
            j++;
        }
        if (j<zombiesList.size()-1 || bulletsList.at(k).getPosition().getX()>sizeX*BoardSquare::size) {
            bulletsList.erase(bulletsList.begin() + k);
        }else {
            bulletsList.at(k).draw();
        }
    }
    

	UpdateSunScreenCoordinate();
    for (int l=0; l<sunList.size(); l++) {
        if (sunList[l].getDespawn() > 0) {
            sunList[l].draw();
        }
        else {
            sunList.erase(sunList.begin()+l);
        }
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
    for (int i = 0; i < squaresList.size(); i++)
    {
        Plant* plant = squaresList.at(i).getPlant();
        if (plant != nullptr) {
            if (plant->getType() == "PEASHOOTER"){
                addBullet(((PeaShooter*)plant)->shoot());
            }
            
            if (plant->getType() == "SUNPLANT") {
                addSun(((SunPlant*)plant)->produceSun());
            }
        }
    }
    
}

void Gameboard::UpdateBullets() {
    for (int i=0; i<bulletsList.size(); i++) {
        if (bulletsList.at(i).getPosition().getX() != 0 && bulletsList.at(i).getPosition().getZ()!=0) {
            bulletsList.at(i).move();
            
        }
    }
}

void Gameboard::UpdateSunScreenCoordinate()
{

	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLdouble winX, winY, winZ;
	GLdouble prevwinX, prevwinY, prevwinZ;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);//!!!!!!!!!!!!!!!!!!!!!
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	/*std::cout << "____________________________________" << std::endl;
	std::cout << projection[0] << "  " << projection[4] << "  " << projection[8] << "  " << projection[12] << std::endl;
	std::cout << projection[1] << "  " << projection[5] << "  " << projection[9] << "  " << projection[13] << std::endl;
	std::cout << projection[2] << "  " << projection[6] << "  " << projection[10] << "  " << projection[14] << std::endl;
	std::cout << projection[3] << "  " << projection[7] << "  " << projection[11] << "  " << projection[15] << std::endl;*/
	/*std::cout << "____________________________________" << std::endl;
	std::cout << modelview[0] << "  " << modelview[4] << "  " << modelview[8] << "  " << modelview[12] << std::endl;
	std::cout << modelview[1] << "  " << modelview[5] << "  " << modelview[9] << "  " << modelview[13] << std::endl;
	std::cout << modelview[2] << "  " << modelview[6] << "  " << modelview[10] << "  " << modelview[14] << std::endl;
	std::cout << modelview[3] << "  " << modelview[7] << "  " << modelview[11] << "  " << modelview[15] << std::endl;*/

	for (unsigned i = 0; i<sunList.size(); i++)
	{
		gluProject((int)sunList[i].getPosition().getX(), (int)sunList[i].getPosition().getY(), (int)sunList[i].getPosition().getZ(),
			modelview, projection, viewport,
			&winX, &winY, &winZ);
		
		sunList[i].setScreencoordX( winX);
		sunList[i].setScreencoordY(glutGet(GLUT_WINDOW_HEIGHT) - winY);
		std::cout << "winX =    " << winX << std::endl;
		//std::cout << "sunX =    " << sunList[i].getScreenCoordX() << std::endl;
		std::cout << "winY =    " << winY << std::endl;
		//std::cout << "sunY =    " << sunList[i].getScreenCoordY() << std::endl;*/
	}

}

void Gameboard::checkSunHoveringStatus(int x, int y)//x, y being the mouse position on screen
{
	double distance = 0.0f;
	double minDistance = 20.0f;
	int hoveredSun = -1;
	for (unsigned i = 0; i < sunList.size(); i++)
	{
		sunList[i].setIsHovered(false);
		distance = sqrt((x - sunList[i].getScreenCoordX())*(x - sunList[i].getScreenCoordX())
			+ (y - sunList[i].getScreenCoordY())*(y - sunList[i].getScreenCoordY()));
		std::cout << "distance " << distance << " sunId  " << i << std::endl;
		//if (distance > 50) continue;
		if (distance < minDistance)
		{
			hoveredSun = i;
			minDistance = distance;
		}
	}
	if (hoveredSun != -1) sunList[hoveredSun].setIsHovered(true);
}


int Gameboard::selectSun(){
		for (unsigned i = 0; i<sunList.size(); i++)
		{
			if (sunList[i].getIsHovered())
			{
				sunList[i].setDespawn(0);
				return 50;
			}
		}
		return 0;
}

void Gameboard::UpdateSuns() {
    for (int i=0; i<sunList.size(); i++) {
        sunList[i].update();
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
