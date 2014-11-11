#include "Plant.h"

Plant::Plant() {
	hp = 5;
	coolDown = 0;
}

Plant::Plant(int cooldown) : Plant() {
	setCooldown(cooldown);	
}

Plant::Plant(int cooldown, int hp) : Plant(cooldown) {
	setHp(hp);	
}

int Plant::getHp() {
	return hp;
}
    
void Plant::setHp(int hp) {
	this->hp = hp;
}
    
int Plant::getCooldown() {
	return coolDown;
}

void Plant::setCooldown(int cooldown) {
	this->coolDown = cooldown;
}
