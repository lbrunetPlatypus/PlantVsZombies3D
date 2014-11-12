#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "BoardSquare.h"
#include <vector>
#include "Position.h"
#include "GameObject.h"
#include <ctime>

class Gameboard {
    private :
    std::vector<BoardSquare> squaresList;
    
    public :
    void addObject(GameObject object, Position position);
    void deleteObject(Position position);
};

#endif