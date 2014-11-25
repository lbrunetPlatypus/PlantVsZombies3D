#include "BoardSquare.h"

BoardSquare::BoardSquare(int _x, int _z, int _id){
	id = _id;
	x = _x;
	z = _z;
	plant = nullptr;
}

void BoardSquare::setX(int _x){
	x = _x;
}

void BoardSquare::setZ(int _z){
	z = _z;
}

void BoardSquare::set2DPosition(int _x, int _z){
	x = _x;
	z = _z;
}

void BoardSquare::setId(int _id){
	id = _id;
}

int BoardSquare::getX(){
	return x;
}

int BoardSquare::getZ(){
	return z;
}

Position BoardSquare::get2DPosition(){
	return Position(x, 0, z);
}

int BoardSquare::getId(){
	return id;
}


Plant* BoardSquare::getPlant(){
	return plant;
}

void BoardSquare::setPlant(Plant* _plant){
	plant=_plant;
}

void BoardSquare::draw(GLuint texture[]) {
    glPushMatrix();
        //draw grass
        glColor3f(0, 0.6, 0);
        glBegin(GL_QUADS);
            glVertex3f(x*size, 0, z*size);
            glVertex3f((x+1)*size, 0, z*size);
            glVertex3f((x+1)*size, 0, (z+1)*size);
            glVertex3f(x*size, 0, (z+1)*size);
        glEnd();
        //draw ground cube
        glColor3f(0.55, 0.27, 0);
        glTranslatef((x+0.5)*size, -size/2-1, (z+0.5)*size);
        glutSolidCube(size);
    glPopMatrix();
}

float BoardSquare::getScreenCoordX(){
	return BoardSquare::screenCoordX;
}

float BoardSquare::getScreenCoordY(){
	return BoardSquare::screenCoordY;
}

void BoardSquare::setScreencoordX(float _screenCoordX){
	screenCoordX = _screenCoordX;
}

void BoardSquare::setScreencoordY(float _screenCoordY){
	screenCoordY = _screenCoordY;
}

bool BoardSquare::getIsHovered(){
	return BoardSquare::isHovered;
}

void BoardSquare::setIsHovered(bool status){
	isHovered = status;
}


