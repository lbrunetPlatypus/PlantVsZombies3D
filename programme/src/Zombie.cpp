#include "Zombie.h"

 bool Zombie::detectTarget(){

	 return true;
}

void Zombie::move(){
	setPosition(getPosition()+Position(1*speed,0,0));
}

void Zombie::nibble(){//makedamages to the objet in front
}

bool Zombie::takeDamages(int nbDamages){
	hp -= nbDamages;
	if (hp <= 0){
		return true;
	}
	else{
		return false;
	}
	
}