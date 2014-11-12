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
}

void BoardSquare::setObject(GameObject _object){
	//set object position at the same time?
	object = _object;
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
GameObject BoardSquare::getObject(){
	return object;
}
int BoardSquare::getId(){
	return id;
}

Vec3 BoardSquare::getScreenCoordinate() {
    return screenCoordinate;
}


void BoardSquare::setHoveringStatus(bool status) {
    isHovered = status;
}
bool BoardSquare::getHoveringStatus() {
    return isHovered;
}



