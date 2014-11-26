#include "BoardSquare.h"
#include <iostream>

GLfloat* Normal (GLfloat p00, GLfloat p01, GLfloat p02,
                 GLfloat p10, GLfloat p11, GLfloat p12,
                 GLfloat p20, GLfloat p21, GLfloat p22) {
    
    GLfloat* n = (GLfloat*)malloc(3*sizeof(GLfloat));
    
    float x3, y3, z3, x4, y4, z4; //t: (x3, y3, z3), r: (x4, y4, z4)
    x3 = p10 - p00; y3 = p11 - p01; z3 = p12 - p02; //t=P1-P0
    x4 = p20 - p00; y4 = p21 - p01; z4 = p22 - p02; //r=P2-P0
    // n = t x r. ‘x is the cross-product. u is perpendicular to the plane
    n[0] = y3*z4 - y4*z3; n[1] = -(x3*z4 - x4*z3); n[2] = x3*y4 - x4*y3;
    
    return n;
}

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
    GLfloat* n;
    glPushMatrix();
        //draw grass
        glColor3f(0, 0.6, 0);
		if (isHovered){
			glColor3f(0, 0.9, 0);
		}
        n = Normal(x*size, 0, z*size,
                   (x+1)*size, 0, (z+1)*size,
                   (x+1)*size, 0, z*size);
        glBegin(GL_QUADS);
            glNormal3f(n[0],n[1],n[2]);
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


