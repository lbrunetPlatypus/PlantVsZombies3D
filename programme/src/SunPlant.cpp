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
    x += 100;
    glutPostRedisplay();
}

void SunPlant::draw() {
    glPushMatrix();
    glTranslatef(x, 0, 0);
    glColor3f(0, 1, 0);
    gluSphere(gluNewQuadric(), 200, 20, 20);
    glPopMatrix();
}