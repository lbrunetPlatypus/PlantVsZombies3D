#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Gameboard.h"

class Game {

    private :
    Player player;
    GameBoard gameboard;
    int score;
    
    public :
    play();
    updateScore();
}
#endif
