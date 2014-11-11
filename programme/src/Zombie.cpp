#include "Zombie.h""

 bool Zombie::detectTarget(){

	 return true;
}

void Zombie::move(){
	setPosition(getPosition()+1);
}
void Zombie::nibble(){
}
bool Zombie::takeDamages(){
	return true;
}