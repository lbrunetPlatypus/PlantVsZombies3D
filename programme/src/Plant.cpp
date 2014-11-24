#include "Plant.h"


Plant::Plant() {
	hp = 5;
	coolDown = 0;
    coolDownState = coolDown;
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

int Plant::getCooldownState() {
    return coolDownState;
}

void Plant::setCooldownState(int cooldownstate) {
    coolDownState = cooldownstate;
}

bool Plant::ApplyDamages(int nbDamages){//return true if plant dies
	hp -= nbDamages;
	if (hp <= 0){
		return true;
	}
	else{
		return false;
	}

}

std::string Plant::getType() {
    return "";
}
