#include "Zombie.h"

 bool Zombie::detectTarget(){

	 return true;
}

void Zombie::move(){
    Position position = getPosition();
    position = position + Position(100, 0, 0);
    setPosition(position);
    glutPostRedisplay();
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

void Zombie::draw() {
    glPushMatrix();
    glTranslatef(getPosition().getX(), getPosition().getY(), getPosition().getZ());
    glColor3f(1, 0, 0);
    gluSphere(gluNewQuadric(), 40, 20, 20);
    glPopMatrix();
}