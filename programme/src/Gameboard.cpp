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

//spawn zombies
void Gameboard::zombieSpawn(Zombie &zombie) {
    //set a line to the zombie
    zombie.setPosition(Position(sizeX*BoardSquare::size, 0, (rand()%5+0.5)*BoardSquare::size));
    //add it to the list of zombies
    zombiesList.push_back(&zombie);
}

//Produce a sun at a position
void Gameboard::produceSun(Position position) {
    //create a sun
    Sun sun;
    //get the square thanks to the position
    BoardSquare square = getSquare(position);
    //set the position to 30 in front of the center of the square
    sun.setPosition(Position((square.getX()+0.5)*BoardSquare::size, 0, (square.getZ()+0.5)*BoardSquare::size+30));
    //add it !
    sunList.push_back(sun);
}

//add a Sun on the board
void Gameboard::addSun(Sun sun) {
    //if the sun is well defined ie not in (0,0,0)
    if (sun.getPosition().getX() != 0 && sun.getPosition().getZ() != 0) {
        //add it
        sunList.push_back(sun);
    }
}

//add a plant on a square of the gameboard
bool Gameboard::addPlant(Plant* object,int squareId){
	//set object position using the square?
    BoardSquare square = squaresList[squareId];
    //if the sqaure doesn't already have a plant
    if (square.getPlant() ==nullptr) {
        //set the position to the center of the square
        object->setPosition(Position((square.getX()+0.5)*BoardSquare::size, 0, (square.getZ()+0.5)*BoardSquare::size));
        //set plant to the square
        squaresList[squareId].setPlant(object);
        return true;
    }
    return false;
	
}

//add a bullet on the gameboard
void Gameboard::addBullet(Bullet bullet) {
    //the bullet is defined ie not positionned on (0,0,0)
    if (bullet.getPosition().getX() != 0 && bullet.getPosition().getZ() != 0) {
        //add it !
        bulletsList.push_back(bullet);
    }
}

BoardSquare Gameboard::getSquare(Position position){
    int i,j;
    i = position.getX()/BoardSquare::size;
    j = position.getZ()/BoardSquare::size;
    
    return getSquaresList().at(sizeZ*i+j);
}

void Gameboard::draw(GLuint texture[], float animPos, float plantAnimPos) {
	UpdateSquareScreenCoordinate();

	house.draw(texture, getSizeZ() * 100, getSizeZ() * 100 / 3, getSizeZ() * 100 / 3);
    
    //draw all Plants and Squares
    for (int i=0; i<squaresList.size(); i++) {
        //draw the board square
        squaresList[i].draw(texture);
        //check if the board square contain a plant
        if (squaresList.at(i).getPlant() != nullptr) {
            //check if the plant has enough HP
            if ((squaresList.at(i).getPlant())->getHp() > 0) {
                //draw the plant with the texture
				squaresList.at(i).getPlant()->draw(texture, plantAnimPos);
            }else {
                //erase the plant from the square
                squaresList.at(i).setPlant(nullptr);
            }
        }
    }
    
    //draw all zombies
    for (int j=0; j<zombiesList.size(); j++) {
        //check if the zombie has enough HP
        if (zombiesList[j]->takeDamages(0) && zombiesList[j]->getDespawn()<=0) {
            //delete the zombie from zombiesList
            zombiesList.erase(zombiesList.begin()+j);
        } else {
            //else draw the zombie with the texture
            zombiesList[j]->draw(texture, animPos);
        }
    }
    
    //draw all bullets shoot by peashooters
    for (int k=0; k<bulletsList.size(); k++) {
        //iterator
        int j=0;
        //check for each zombie
        //while the zombieslist is not empty AND do not collide with the bullet
        while (!zombiesList.empty() && !bulletsList.at(k).checkCollision(*zombiesList.at(j)) && j<zombiesList.size()-1 ) {
            //check next zombie
            j++;
        }
        
        //if there is still zombies
        if (!zombiesList.empty()) {
            //if there is a collision with a zombie OR a the border
            if (bulletsList.at(k).checkCollision(*zombiesList.at(j)) || bulletsList.at(k).getPosition().getX()>sizeX*BoardSquare::size) {
                //erase the bullet
                bulletsList.erase(bulletsList.begin() + k);
            }else {
                //draw the bullet
                bulletsList.at(k).draw(texture);
            }
        }
        //if there is no zombie left
        else {
            //if the bullet collide with the border
            if (bulletsList.at(k).getPosition().getX()>sizeX*BoardSquare::size) {
                //erase the bullet
                bulletsList.erase(bulletsList.begin() + k);
            }else {
                //draw the bullet
                bulletsList.at(k).draw(texture);
            }
        }
        
    }
    
	UpdateSunScreenCoordinate();
    
    //draw all suns
    for (int l=0; l<sunList.size(); l++) {
        //if the sun has not reached his despawn time
        if (sunList[l].getDespawn() > 0) {
            //draw the sun
            sunList[l].draw(texture);
        }
        //if has reached
        else {
            //erase the sun
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
					zombiesList[i]->nibble(*tempPlant);
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

//Update plants
void Gameboard::UpdatePlants() {
    //for each squarelist
    for (int i = 0; i < squaresList.size(); i++)
    {
        Plant* plant = squaresList.at(i).getPlant();
        //if there is a plant
        if (plant != nullptr) {
            //if the plant is a Peashooter
            if (plant->getType() == "PEASHOOTER"){
                //if there are zombies
                if (!zombiesList.empty())
                    //shoot !
                    addBullet(((PeaShooter*)plant)->shoot());
            }
            
            //if the plant is a Sunplant
            if (plant->getType() == "SUNPLANT") {
                //add a sun
                addSun(((SunPlant*)plant)->produceSun());
            }
        }
    }
    
}

//Update bullets
void Gameboard::UpdateBullets() {
    //for each bullet
    for (int i=0; i<bulletsList.size(); i++) {
        //if the bullet is not defined that means that the bullet is placed a (0,0,0)
        if (bulletsList.at(i).getPosition().getX() != 0 && bulletsList.at(i).getPosition().getZ()!=0) {
            //move the bullet !
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
		//std::cout << "winX =    " << winX << std::endl;
		//std::cout << "sunX =    " << sunList[i].getScreenCoordX() << std::endl;
		//std::cout << "winY =    " << winY << std::endl;
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
		//std::cout << "distance " << distance << " sunId  " << i << std::endl;
		//if (distance > 50) continue;
		if (distance < minDistance)
		{
			hoveredSun = i;
			minDistance = distance;
		}
	}
	if (hoveredSun != -1) sunList[hoveredSun].setIsHovered(true);
}

int Gameboard::checkSquareHoveringStatus(int x, int y){
	double distance = 0.0f;
	double minDistance = 200.0f;
	int hovered = -1;
	for (unsigned i = 0; i < squaresList.size(); i++)
	{
		squaresList[i].setIsHovered(false);
		distance = sqrt((x - squaresList[i].getScreenCoordX())*(x - squaresList[i].getScreenCoordX())
			+ (y - squaresList[i].getScreenCoordY())*(y - squaresList[i].getScreenCoordY()));
		
		if (distance < minDistance)
		{
			hovered = i;
			minDistance = distance;
			//std::cout << "distance " << distance << " squareId  " << i << std::endl;
		}
	}
	if (hovered != -1){
		squaresList[hovered].setIsHovered(true);
		return hovered;
	}
	else	
		return -1;
	//if (hovered != -1) squaresList[hovered].setIsHovered(true);
}


void Gameboard::UpdateSquareScreenCoordinate(){

	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLdouble winX, winY, winZ;
	GLdouble prevwinX, prevwinY, prevwinZ;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	for (unsigned i = 0; i < squaresList.size(); i++)
	{
		// attention x correspond aux colonnes (sizez) et y au ligne (sizex...
		int posX = (int)squaresList[i].getX()* 100 + 50;
		int posZ = (int)squaresList[i].getZ() * 100 + 50;
		gluProject(posX, 0, posZ,
			modelview, projection, viewport,
			&winX, &winY, &winZ);

		squaresList[i].setScreencoordX(winX);
		squaresList[i].setScreencoordY(glutGet(GLUT_WINDOW_HEIGHT) - winY);
		/*std::cout << "__________________________________________________" << i << std::endl;
		
		std::cout << "ligne =    " << squaresList[i].getZ() <<  "posx =    " << posX << std::endl;
		std::cout << "colone =    " << squaresList[i].getX() << "posZ =    " << posZ << std::endl;
		
		std::cout << "squareX =    " << squaresList[i].getScreenCoordX() << std::endl;
		std::cout << "squareY =    " << squaresList[i].getScreenCoordY() << std::endl; */

	}
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

//Update suns
void Gameboard::UpdateSuns() {
    //for each sun
    for (int i=0; i<sunList.size(); i++) {
        //up to date
        sunList[i].update();
    }
}

bool Gameboard::isGameover() {
    for (int i=0; i<zombiesList.size(); i++) {
        if (zombiesList[i]->getPosition().getX() <= 0) {
            return true;
        }
    }
    return false;
}

void Gameboard::setHouse(House _house){
	house = _house;
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


