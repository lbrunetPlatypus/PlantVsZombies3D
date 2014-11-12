#include "Gameboard.h"


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

void Gameboard::addObject(GameObject object,int squareId){
	//set object position using the square?
	squaresList[squareId].setObject(object);
	
}

void Gameboard::deleteObject(int squareId){

}