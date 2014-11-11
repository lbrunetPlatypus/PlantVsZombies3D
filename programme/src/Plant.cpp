#include "Plant.h"

Plant::Plant() {
	hp = 5;
	cooldown = 0;
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
	return cooldown;
}

void Plant::setCooldown(int cooldown) {
	this->cooldown = cooldown;
}
