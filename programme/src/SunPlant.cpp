#include "SunPlant.h"
#include <math.h>
# define PI 3.14159265358979323846  /* pi */

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
    int nPetals = 20;
    int petalLength = 10;
    int sunRadius = 40;
    glPushMatrix();
    glTranslatef(getPosition().getX(), 0, getPosition().getZ());
    glColor3f(1, 1, 0);
    
    
    glPushMatrix();
        glTranslatef(0, 50, 0);
        glScalef(1, 0.7, 1);
        for (int i=0; i<nPetals; i++) {
            glPushMatrix();
            glTranslatef(0, (sunRadius+petalLength/2)*cos(i*(2*PI/nPetals)), (sunRadius+petalLength/2)*sin(i*(2*PI/nPetals)));
            glRotatef(i*(360/nPetals), 1, 0, 0);
            glScalef(5, petalLength, 2*PI*sunRadius/nPetals/1.5);
            gluSphere(gluNewQuadric(), 1, 20, 20);
            glPopMatrix();
        }
        glColor3f(0.55, 0.27, 0);

        glPushMatrix();
            glScalef(0.33, 1, 1);
            gluSphere(gluNewQuadric(), sunRadius, 20, 20);
        glPopMatrix();
        
    glPopMatrix();
    
    glColor3f(0, 1, 0);
    glPushMatrix();
    glTranslatef(0, 20, 0);
        glRotatef(90, 1, 0, 0);
        gluCylinder(gluNewQuadric(), 5, 5, 50, 20, 20);
    glPopMatrix();
    glPopMatrix();
}