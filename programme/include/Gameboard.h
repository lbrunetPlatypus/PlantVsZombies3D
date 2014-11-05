#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "BoardSquare.h"
#include <vector>
#include "Position.h"
#include "GameObject.h"
class Gameboard {
    private :
    squaresList : vector<BoardSquare>;
    
    public :
    addObject(GameObject object, Position position);
    deleteObject(Position position);
};

#endif