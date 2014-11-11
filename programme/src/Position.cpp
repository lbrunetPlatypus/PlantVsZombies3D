#include "Position.h"

Position::Position(){
	x = 0;
	y = 0;
	z = 0;
}

Position::Position(int _x, int _y, int _z){
	x = _x;
	y = _y;
	z = _z;
}

int Position::getX(){
	return x;
}
int Position::getY(){
	return y;
}
 int Position::getZ(){
	return z;
}
void Position::setPosition(int _x, int _y, int _z){
	x = _x;
	y = _y;
	z = _z;
}

void Position::setPosition(Position pos){
	x = pos.getX();
	y = pos.getY();
	z = pos.getZ();
}

Position Position::operator + (const Position& pos1){
	Position result, pos = pos1;
	result.setPosition(getX() + pos.getX(), pos.getY() + getY(), pos.getZ() + getZ());
	return result;
}


