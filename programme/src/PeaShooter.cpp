#include "PeaShooter.h"
#include <math.h>
#define PI 3.14159265358979323846

void drawTorus(double ra, double rb, int slices, int stacks) {
    for (int i=0; i<slices; i++) {
        for (int j=0; j<stacks; j++) {
            glBegin(GL_QUADS);
            glVertex3f((ra+rb*cos(i*2*PI/slices))*cos(j*2*PI/stacks), (ra+rb*cos(i*2*PI/slices))*sin(j*2*PI/stacks), rb*sin(i*2*PI/slices));
            glVertex3f((ra+rb*cos((i+1)*2*PI/slices))*cos(j*2*PI/stacks), (ra+rb*cos((i+1)*2*PI/slices))*sin(j*2*PI/stacks), rb*sin((i+1)*2*PI/slices));
            glVertex3f((ra+rb*cos((i+1)*2*PI/slices))*cos((j+1)*2*PI/stacks), (ra+rb*cos((i+1)*2*PI/slices))*sin((j+1)*2*PI/stacks), rb*sin((i+1)*2*PI/slices));
            glVertex3f((ra+rb*cos(i*2*PI/slices))*cos((j+1)*2*PI/stacks), (ra+rb*cos(i*2*PI/slices))*sin((j+1)*2*PI/stacks), rb*sin(i*2*PI/slices));
            glEnd();
        }
    }
}

PeaShooter::PeaShooter() {
    setHp(30);
    setPosition(Position(0,0,0));
    setCooldown(10);
    setCooldownState(0);
}

PeaShooter::PeaShooter(int attackPoint) {
	setAttackPoint(attackPoint);
}

int PeaShooter::getAttackPoint() {
	return attackPoint;
}

void PeaShooter::setAttackPoint(int ap) {
	attackPoint = ap;
}

void PeaShooter::detectZombie() {

}

std::string PeaShooter::getType() {
    return "PEASHOOTER";
}

void PeaShooter::draw(GLuint texture[], float plantAnimPos) {
    int mouthRadius = 15;
    int mouthLength = 0;
    int angle = 0;
    if (getCooldownState() >= 2 && getCooldownState() <= 4){
        angle = (4 - getCooldownState())*5;
    } else if (getCooldownState() < 2 ) {
        mouthRadius = 15;
        mouthRadius -= (2-getCooldownState())*3;
        mouthLength += (2-getCooldownState())*2;
        angle = getCooldownState()*5 + 5;
        
    }else if (getCooldownState() > 7){
        mouthRadius = 7;
        mouthRadius += (getCooldown()-getCooldownState()+1)*2;
        angle = 0;
        
    }

    GLUquadric* leavesquad = gluNewQuadric(), *stemquad = gluNewQuadric(), *peaface = gluNewQuadric();
    glEnable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texture[9]);
    gluQuadricTexture(peaface,1);

    int slices = 10;
    int stacks = 10;
    int r = 10;
    
    glPushMatrix();
    glTranslatef(getPosition().getX(), getPosition().getY(), getPosition().getZ());
    glColor3f(0.5, 1, 0);
    glTranslatef(0, 80, 0);
    
    glPushMatrix();
    glTranslatef(0, -80, 0);
    glRotatef(angle, 0, 0, 1);
    glTranslatef(0, 80, 0);
    //head
    glPushMatrix();
    glTranslatef(-10, -5, 0);
    glPushMatrix();
    glScalef(1, 0.9, 1);
    gluSphere(peaface, 30, 20, 20);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    gluQuadricTexture(leavesquad,1);
    glColor3f(0, 1, 0);
    //back head leaf
    glPushMatrix();

    glTranslatef(-35, 10, 0);
    glRotatef(-30, 0, 0, 1);
    glRotatef(-90, 1, 0, 0);
    glScalef(1.5, 0.5, 0.5);
    for (int j=0;j<10; j++) {
        for (int i=0;i<10;i++) {
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
    
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    gluQuadricTexture(stemquad,1);
    //mouth 1
        glPushMatrix();
        glColor3f(0.5, 1, 0);
        glTranslatef(50, 0, 0);
        glRotatef(90, 0, 1, 0);
        drawTorus(mouthRadius+3, 2, 20, 20);
        glPopMatrix();
        glColor3f(0, 1, 0);
    //mouth 2
        glPushMatrix();
        glColor3f(0.5, 1, 0);
        glTranslatef(20, 0, 0);
        glRotatef(90, 0, 1, 0);
        gluCylinder(stemquad, 10, mouthRadius+5, 30+mouthLength, 20, 20);
        glColor3f(0, 0, 0);
        gluCylinder(stemquad, 10, mouthRadius+2, 30+mouthLength, 20, 20);
        glTranslatef(mouthLength, 0, 10);
        gluSphere(stemquad, mouthRadius-3, 20, 20);
        glPopMatrix();
    //mouth3
        glColor3f(0.5, 1, 0);
        glPushMatrix();
        glTranslatef(32, 0, 0);
        glRotatef(-90, 0, 1, 0);
        gluCylinder(stemquad, 10, 20, 10, 20, 20);
        glPopMatrix();
    
    glPopMatrix();
    

    //stem
    glTranslatef(0, -52, 0);
    glColor3f(0, 1, 0);
    glPushMatrix();
    glTranslatef(-10, 25, 0);
    glRotatef(90, 1, 0, 0);
    gluCylinder(stemquad, 5, 5, 50, 20, 20);
    glPopMatrix();
    
    glPopMatrix();
    
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    gluQuadricTexture(leavesquad,1);
    
    glTranslatef(0, -52, 0);

    //leaves
    glPushMatrix();
    glScalef(1.5, 1, 1);
    
    glTranslatef(-5, -25, 15);
    glRotatef(-90, 1, 0, 0);
    for (int j=0;j<10; j++) {
        for (int i=0;i<10;i++) {
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
    for (int j=0;j<10; j++) {
        for (int i=0;i<10;i++) {
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
    for (int j=0;j<10; j++) {
        for (int i=0;i<10;i++) {
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
    for (int j=0;j<10; j++) {
        for (int i=0;i<10;i++) {
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

Bullet PeaShooter::shoot() {
    if (getCooldownState()==0) {
        setCooldownState(getCooldown());
        Bullet bullet;
        bullet.setPosition(getPosition()+Position(10, 75, 0));
        return bullet;
    } else {
        setCooldownState(getCooldownState()-1);
        return Bullet();
    }

}