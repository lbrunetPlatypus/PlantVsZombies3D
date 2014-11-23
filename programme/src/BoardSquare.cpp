#include "BoardSquare.h"	

BoardSquare::BoardSquare(){
	id = 0;
	x = 0;
	z = 0;

}

BoardSquare::BoardSquare(int _x, int _z, int _id){
	id = _id;
	x = _x;
	z = _z;
    //object = nullptr;
	plant = nullptr;
}

//void BoardSquare::setObject(GameObject* _object){
//	//set object position at the same time?
//	object = _object;
//}
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
//GameObject* BoardSquare::getObject(){
//	return object;
//}
int BoardSquare::getId(){
	return id;
}

Vec3 BoardSquare::getScreenCoordinate() {
    return screenCoordinate;
}

Plant* BoardSquare::getPlant(){
	return plant;
}

void BoardSquare::setPlant(Plant* _plant){
	plant=_plant;
}

void BoardSquare::draw() {
    glPushMatrix();
    glColor3f(0, 0.6, 0);
    glBegin(GL_QUADS);
    glVertex3f(x*size, 0, z*size);
    glVertex3f((x+1)*size, 0, z*size);
    glVertex3f((x+1)*size, 0, (z+1)*size);
    glVertex3f(x*size, 0, (z+1)*size);
    glEnd();
    glColor3f(0.55, 0.27, 0);
    glTranslatef((x+0.5)*size, -size/2-1, (z+0.5)*size);
    glutSolidCube(size);
    glPopMatrix();
}

void BoardSquare::setHoveringStatus(bool status) {
    isHovered = status;
}
bool BoardSquare::getHoveringStatus() {
    return isHovered;
}



