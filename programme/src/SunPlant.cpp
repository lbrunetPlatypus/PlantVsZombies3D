#include "SunPlant.h"
int x=0;

SunPlant::SunPlant(): Plant() {

}

SunPlant::SunPlant(int cooldown) : Plant(cooldown) {

}

SunPlant::SunPlant(int cooldown, int hp) : Plant(cooldown,hp) {

}

void SunPlant::produceSun() {
	//call gameboard in order to produce a sun.
    Position position = getPosition();
    position = position + Position(100, 0, 0);
    setPosition(position);
    glutPostRedisplay();
}

void SunPlant::draw() {
    glPushMatrix();
    glTranslatef(getPosition().getX(), 0, getPosition().getZ());
    glColor3f(0, 1, 0);
    gluSphere(gluNewQuadric(), 40, 20, 20);
    glPopMatrix();
}