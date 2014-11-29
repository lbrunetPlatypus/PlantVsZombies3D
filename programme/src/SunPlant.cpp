#include "SunPlant.h"
#include <math.h>
#include <iostream>
# define PI 3.14159265358979323846  /* pi */

int x=0;


SunPlant::SunPlant(): Plant() {
    setHp(30);
    setPosition(Position(0,0,0));
    setCooldown(10);
    setCooldownState(getCooldownState());
    
}

SunPlant::SunPlant(int cooldown) : Plant(cooldown) {

}

SunPlant::SunPlant(int cooldown, int hp) : Plant(cooldown,hp) {

}

Sun SunPlant::produceSun() {

	//call gameboard in order to produce a sun.
    if (getCooldownState() == 0) {
		std::cout << "suuuuuun" << std::endl;
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

void SunPlant::draw(GLuint texture[], float plantAnimPos) {
    int nPetals = 20;
    int petalLength = 10;
    int sunRadius = 40;
    int slices = 10;
    int stacks = 10;
    int r = 10;

    GLUquadric* leavesquad = gluNewQuadric(), *petalsquad = gluNewQuadric(), *stemquad = gluNewQuadric(), *flowerQuad = gluNewQuadric();
    
    //GlPush
	//glTranslate(5-plantAnim,0,0)
	//Head
	//GlPop

    glPushMatrix();
    glTranslatef(getPosition().getX(), 30, getPosition().getZ());
    glColor3f(1, 1, 0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    gluQuadricTexture(petalsquad,1);
    //draw petals
    glPushMatrix();
    glTranslatef(0, 50, 0);
    glScalef(1, 0.7, 1);
    for (int i=0; i<nPetals; i++) {
        glPushMatrix();
        glTranslatef(0, (sunRadius+petalLength/2)*cos(i*(2*PI/nPetals)), (sunRadius+petalLength/2)*sin(i*(2*PI/nPetals)));
        glRotatef(i*(360/nPetals), 1, 0, 0);
        glScalef(5, petalLength, 2*PI*sunRadius/nPetals/1.5);
        gluSphere(petalsquad, 1, 20, 20);
        glPopMatrix();
    }
    


    glBindTexture(GL_TEXTURE_2D, texture[2]);
    gluQuadricTexture(flowerQuad,1);

    glColor3f(1, 1, 1);
    
    glPushMatrix();
    glScalef(0.33, 1, 1);
    gluSphere(flowerQuad, sunRadius, 20, 20);
    glPopMatrix();

    
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    gluQuadricTexture(stemquad,1);
    glColor3f(0, 1, 0);
    
    glPushMatrix();
    glTranslatef(-5, 0, 0);
    glScalef(0.33, 1, 1);
    gluSphere(stemquad, sunRadius, 20, 20);
    glPopMatrix();
    

    
    glPopMatrix();
    glColor3f(0, 1, 0);
    
    glPushMatrix();
    glTranslatef(-10, 25, 0);
    glRotatef(90, 1, 0, 0);
    gluCylinder(stemquad, 5, 5, 50, 20, 20);
    glPopMatrix();
    
    
    //draw Leaves
    glPushMatrix();
    glScalef(1.5, 1, 1);
    
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    gluQuadricTexture(leavesquad,1);
    
    glTranslatef(-5, -25, 15);
    glRotatef(-90, 1, 0, 0);
    for (int i=0; i<slices; i++) {
        for (int j=0; j<stacks; j++) {
            glBegin(GL_QUADS);
            glTexCoord2f(0.5+0.5*cos(i*PI/10)*cos(j*2*PI/10), 0.5+0.5*cos(i*PI/10)*sin(j*2*PI/10));
            glVertex3f(r*cos((i)*PI/slices)*cos((j)*2*PI/stacks), 20*cos((i)*PI/slices)*sin((j)*2*PI/stacks), r*sin((i)*PI/slices));
            glTexCoord2f(0.5+0.5*cos(i*PI/10)*cos((j+1)*2*PI/10), 0.5+0.5*cos(i*PI/10)*sin((j+1)*2*PI/10));
            glVertex3f(r*cos((i)*PI/slices)*cos((j+1)*2*PI/stacks), 20*cos((i)*PI/slices)*sin((j+1)*2*PI/stacks), r*sin((i)*PI/slices));
            glTexCoord2f(0.5+0.5*cos((i+1)*PI/10)*cos((j+1)*2*PI/10), 0.5+0.5*cos((i+1)*PI/10)*2*sin((j+1)*2*PI/10));
            glVertex3f(r*cos((i+1)*PI/slices)*cos((j+1)*2*PI/stacks), 20*cos((i+1)*PI/slices)*sin((j+1)*2*PI/stacks), r*sin((i+1)*PI/slices));
            glTexCoord2f(0.5+0.5*cos((i+1)*PI/10)*cos(j*2*PI/10), 0.5+0.5*cos((i+1)*PI/10)*sin(j*2*PI/10));
            glVertex3f(r*cos((i+1)*PI/slices)*cos((j)*2*PI/stacks), 20*cos((i+1)*PI/slices)*sin((j)*2*PI/stacks), r*sin((i+1)*PI/slices));
            glEnd();
        }

    }
    glPopMatrix();
    
    glRotatef(90, 0, 1, 0);
    glPushMatrix();
    glScalef(1.5, 1, 1);
    
    glTranslatef(-5, -25, 15);
    glRotatef(-90, 1, 0, 0);
    for (int i=0; i<slices; i++) {
        for (int j=0; j<stacks; j++) {
            glBegin(GL_QUADS);
            glTexCoord2f(0.5+0.5*cos(i*PI/10)*cos(j*2*PI/10), 0.5+0.5*cos(i*PI/10)*sin(j*2*PI/10));
            glVertex3f(r*cos((i)*PI/slices)*cos((j)*2*PI/stacks), 20*cos((i)*PI/slices)*sin((j)*2*PI/stacks), r*sin((i)*PI/slices));
            glTexCoord2f(0.5+0.5*cos(i*PI/10)*cos((j+1)*2*PI/10), 0.5+0.5*cos(i*PI/10)*sin((j+1)*2*PI/10));
            glVertex3f(r*cos((i)*PI/slices)*cos((j+1)*2*PI/stacks), 20*cos((i)*PI/slices)*sin((j+1)*2*PI/stacks), r*sin((i)*PI/slices));
            glTexCoord2f(0.5+0.5*cos((i+1)*PI/10)*cos((j+1)*2*PI/10), 0.5+0.5*cos((i+1)*PI/10)*2*sin((j+1)*2*PI/10));
            glVertex3f(r*cos((i+1)*PI/slices)*cos((j+1)*2*PI/stacks), 20*cos((i+1)*PI/slices)*sin((j+1)*2*PI/stacks), r*sin((i+1)*PI/slices));
            glTexCoord2f(0.5+0.5*cos((i+1)*PI/10)*cos(j*2*PI/10), 0.5+0.5*cos((i+1)*PI/10)*sin(j*2*PI/10));
            glVertex3f(r*cos((i+1)*PI/slices)*cos((j)*2*PI/stacks), 20*cos((i+1)*PI/slices)*sin((j)*2*PI/stacks), r*sin((i+1)*PI/slices));
            glEnd();
        }
    }

    glPopMatrix();

    glRotatef(90, 0, 1, 0);
    glPushMatrix();
    glScalef(1.5, 1, 1);
    
    glTranslatef(-5, -25, 15);
    glRotatef(-90, 1, 0, 0);
    for (int i=0; i<slices; i++) {
        for (int j=0; j<stacks; j++) {
            glBegin(GL_QUADS);
            glTexCoord2f(0.5+0.5*cos(i*PI/10)*cos(j*2*PI/10), 0.5+0.5*cos(i*PI/10)*sin(j*2*PI/10));
            glVertex3f(r*cos((i)*PI/slices)*cos((j)*2*PI/stacks), 20*cos((i)*PI/slices)*sin((j)*2*PI/stacks), r*sin((i)*PI/slices));
            glTexCoord2f(0.5+0.5*cos(i*PI/10)*cos((j+1)*2*PI/10), 0.5+0.5*cos(i*PI/10)*sin((j+1)*2*PI/10));
            glVertex3f(r*cos((i)*PI/slices)*cos((j+1)*2*PI/stacks), 20*cos((i)*PI/slices)*sin((j+1)*2*PI/stacks), r*sin((i)*PI/slices));
            glTexCoord2f(0.5+0.5*cos((i+1)*PI/10)*cos((j+1)*2*PI/10), 0.5+0.5*cos((i+1)*PI/10)*2*sin((j+1)*2*PI/10));
            glVertex3f(r*cos((i+1)*PI/slices)*cos((j+1)*2*PI/stacks), 20*cos((i+1)*PI/slices)*sin((j+1)*2*PI/stacks), r*sin((i+1)*PI/slices));
            glTexCoord2f(0.5+0.5*cos((i+1)*PI/10)*cos(j*2*PI/10), 0.5+0.5*cos((i+1)*PI/10)*sin(j*2*PI/10));
            glVertex3f(r*cos((i+1)*PI/slices)*cos((j)*2*PI/stacks), 20*cos((i+1)*PI/slices)*sin((j)*2*PI/stacks), r*sin((i+1)*PI/slices));
            glEnd();
        }
    }

    glPopMatrix();
    glRotatef(90, 0, 1, 0);

    glPushMatrix();
    glScalef(1.5, 1, 1);
    
    glTranslatef(-5, -25, 15);
    glRotatef(-90, 1, 0, 0);
    for (int i=0; i<slices; i++) {
        for (int j=0; j<stacks; j++) {
            glBegin(GL_QUADS);
            glTexCoord2f(0.5+0.5*cos(i*PI/10)*cos(j*2*PI/10), 0.5+0.5*cos(i*PI/10)*sin(j*2*PI/10));
            glVertex3f(r*cos((i)*PI/slices)*cos((j)*2*PI/stacks), 20*cos((i)*PI/slices)*sin((j)*2*PI/stacks), r*sin((i)*PI/slices));
            glTexCoord2f(0.5+0.5*cos(i*PI/10)*cos((j+1)*2*PI/10), 0.5+0.5*cos(i*PI/10)*sin((j+1)*2*PI/10));
            glVertex3f(r*cos((i)*PI/slices)*cos((j+1)*2*PI/stacks), 20*cos((i)*PI/slices)*sin((j+1)*2*PI/stacks), r*sin((i)*PI/slices));
            glTexCoord2f(0.5+0.5*cos((i+1)*PI/10)*cos((j+1)*2*PI/10), 0.5+0.5*cos((i+1)*PI/10)*2*sin((j+1)*2*PI/10));
            glVertex3f(r*cos((i+1)*PI/slices)*cos((j+1)*2*PI/stacks), 20*cos((i+1)*PI/slices)*sin((j+1)*2*PI/stacks), r*sin((i+1)*PI/slices));
            glTexCoord2f(0.5+0.5*cos((i+1)*PI/10)*cos(j*2*PI/10), 0.5+0.5*cos((i+1)*PI/10)*sin(j*2*PI/10));
            glVertex3f(r*cos((i+1)*PI/slices)*cos((j)*2*PI/stacks), 20*cos((i+1)*PI/slices)*sin((j)*2*PI/stacks), r*sin((i+1)*PI/slices));
            glEnd();
        }
    }

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}