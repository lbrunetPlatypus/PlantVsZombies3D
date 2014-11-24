#include "SunPlant.h"
#include <math.h>
# define PI 3.14159265358979323846  /* pi */

int x=0;


SunPlant::SunPlant(): Plant() {
    setPosition(Position(0,0,0));
    setCooldown(5);
    setCooldownState(0);
    
}

SunPlant::SunPlant(int cooldown) : Plant(cooldown) {

}

SunPlant::SunPlant(int cooldown, int hp) : Plant(cooldown,hp) {

}

Sun SunPlant::produceSun() {
	//call gameboard in order to produce a sun.
    if (getCooldownState() <= 0) {
        setCooldownState(getCooldown());
        Sun sun;
        sun.setPosition(getPosition()+Position(0, 0, 30));
        return sun;
    } else {
        setCooldownState(getCooldownState()-1);
        return Sun();
    }
}

std::string SunPlant::getType() {
    return "SUNPLANT";
}

void SunPlant::draw() {
    int nPetals = 20;
    int petalLength = 10;
    int sunRadius = 40;
    glPushMatrix();
    glTranslatef(getPosition().getX(), 30, getPosition().getZ());
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
    
        glColor3f(0, 1, 0);

        glPushMatrix();
        glTranslatef(-5, 0, 0);
        glScalef(0.33, 1, 1);
        gluSphere(gluNewQuadric(), sunRadius, 20, 20);
        glPopMatrix();
    
        glColor3f(0.55, 0.27, 0);

        glPushMatrix();
            glScalef(0.33, 1, 1);
            gluSphere(gluNewQuadric(), sunRadius, 20, 20);
        glPopMatrix();
        
    glPopMatrix();
    
    glColor3f(0, 1, 0);
    glPushMatrix();
    glTranslatef(-10, 25, 0);
        glRotatef(90, 1, 0, 0);
        gluCylinder(gluNewQuadric(), 5, 5, 50, 20, 20);
    glPopMatrix();
    
    
    glPushMatrix();
    glScalef(1.5, 1, 1);
    
    glTranslatef(-5, -25, 15);
    glRotatef(-90, 1, 0, 0);
    for (int j=0;j<10; j++) {
        for (int i=0;i<10;i++) {
            glBegin(GL_QUADS);
            glVertex3f(10*cos(i*PI/10)*cos(j*PI/10), 20*cos(i*PI/10)*sin(j*PI/10), 10*sin(i*PI/10));
            glVertex3f(10*cos((i+1)*PI/10)*cos(j*PI/10), 20*cos((i+1)*PI/10)*sin(j*PI/10), 10*sin((i+1)*PI/10));
            glVertex3f(10*cos((i+1)*PI/10)*cos((j+1)*PI/10), 20*cos((i+1)*PI/10)*sin((j+1)*PI/10), 10*sin((i+1)*PI/10));
            glVertex3f(10*cos(i*PI/10)*cos((j+1)*PI/10), 20*cos(i*PI/10)*sin((j+1)*PI/10), 10*sin(i*PI/10));
            glEnd();
        }
    }
    glPopMatrix();
    
    glRotatef(90, 0, 1, 0);
    glPushMatrix();
    glScalef(1.5, 1, 1);
    
    glTranslatef(-5, -25, 15);
    glRotatef(-90, 1, 0, 0);
    for (int j=0;j<10; j++) {
        for (int i=0;i<10;i++) {
            glBegin(GL_QUADS);
            glVertex3f(10*cos(i*PI/10)*cos(j*PI/10), 20*cos(i*PI/10)*sin(j*PI/10), 10*sin(i*PI/10));
            glVertex3f(10*cos((i+1)*PI/10)*cos(j*PI/10), 20*cos((i+1)*PI/10)*sin(j*PI/10), 10*sin((i+1)*PI/10));
            glVertex3f(10*cos((i+1)*PI/10)*cos((j+1)*PI/10), 20*cos((i+1)*PI/10)*sin((j+1)*PI/10), 10*sin((i+1)*PI/10));
            glVertex3f(10*cos(i*PI/10)*cos((j+1)*PI/10), 20*cos(i*PI/10)*sin((j+1)*PI/10), 10*sin(i*PI/10));
            glEnd();
        }
    }
    glPopMatrix();
    
    glRotatef(90, 0, 1, 0);
    glPushMatrix();
    glScalef(1.5, 1, 1);
    
    glTranslatef(-5, -25, 15);
    glRotatef(-90, 1, 0, 0);
    for (int j=0;j<10; j++) {
        for (int i=0;i<10;i++) {
            glBegin(GL_QUADS);
            glVertex3f(10*cos(i*PI/10)*cos(j*PI/10), 20*cos(i*PI/10)*sin(j*PI/10), 10*sin(i*PI/10));
            glVertex3f(10*cos((i+1)*PI/10)*cos(j*PI/10), 20*cos((i+1)*PI/10)*sin(j*PI/10), 10*sin((i+1)*PI/10));
            glVertex3f(10*cos((i+1)*PI/10)*cos((j+1)*PI/10), 20*cos((i+1)*PI/10)*sin((j+1)*PI/10), 10*sin((i+1)*PI/10));
            glVertex3f(10*cos(i*PI/10)*cos((j+1)*PI/10), 20*cos(i*PI/10)*sin((j+1)*PI/10), 10*sin(i*PI/10));
            glEnd();
        }
    }
    glPopMatrix();
    glRotatef(90, 0, 1, 0);

    glPushMatrix();
    glScalef(1.5, 1, 1);
    
    glTranslatef(-5, -25, 15);
    glRotatef(-90, 1, 0, 0);
    for (int j=0;j<10; j++) {
        for (int i=0;i<10;i++) {
            glBegin(GL_QUADS);
            glVertex3f(10*cos(i*PI/10)*cos(j*PI/10), 20*cos(i*PI/10)*sin(j*PI/10), 10*sin(i*PI/10));
            glVertex3f(10*cos((i+1)*PI/10)*cos(j*PI/10), 20*cos((i+1)*PI/10)*sin(j*PI/10), 10*sin((i+1)*PI/10));
            glVertex3f(10*cos((i+1)*PI/10)*cos((j+1)*PI/10), 20*cos((i+1)*PI/10)*sin((j+1)*PI/10), 10*sin((i+1)*PI/10));
            glVertex3f(10*cos(i*PI/10)*cos((j+1)*PI/10), 20*cos(i*PI/10)*sin((j+1)*PI/10), 10*sin(i*PI/10));
            glEnd();
        }
    }
    glPopMatrix();

    glPopMatrix();
}