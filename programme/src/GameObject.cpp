#include "GameObject.h"
#include <iostream>

GameObject::GameObject() {
    position = Position(0, 0, 0);
}

void GameObject::setPosition(Position newPosition) {
    position = newPosition;
}

Position GameObject::getPosition() {
    return position;
}

void GameObject::draw(){

}

Gameboard* GameObject::getGameboard() {
    return gameboard;
}

void GameObject::setGameboard(Gameboard *_gameboard){
    gameboard = _gameboard;
}


