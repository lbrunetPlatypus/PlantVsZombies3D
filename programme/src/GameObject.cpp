#include "GameObject.h"
#include <iostream>

void GameObject::setPosition(Position newPosition) {
    position = newPosition;
}

Position GameObject::getPosition() {
    return position;
}

void GameObject::draw(){
    std::cout << "go" << std::endl;
}

