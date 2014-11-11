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

const Position operator + (const Position& pos1, const Position& pos2){
	Position result;
	
	result.setPosition(pos1.getX + pos2.getX, pos1.getY + pos2.getY, pos1.getZ + pos2.getZ );
	return result;
}