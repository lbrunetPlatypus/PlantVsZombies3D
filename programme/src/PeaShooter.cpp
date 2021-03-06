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
    setCooldownState(getCooldown());
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
    animation();
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
        glTranslatef(mouthLength, 0, 0);
        glTranslatef(50, 0, 0);
        glRotatef(90, 0, 1, 0);

        drawTorus(mouthRadius+3, 2, 20, 20);
        glPopMatrix();
        glColor3f(0, 1, 0);
    //mouth 2
        glPushMatrix();
        glTranslatef(mouthLength, 0, 0);
        glColor3f(0.5, 1, 0);
        glTranslatef(20, 0, 0);
        glRotatef(90, 0, 1, 0);
        gluCylinder(stemquad, 10, mouthRadius+5, 30, 20, 20);
        glColor3f(0, 0, 0);
        gluCylinder(stemquad, 10, mouthRadius+2, 30, 20, 20);
        glTranslatef(0, 0, 7);
        gluSphere(stemquad, 12, 20, 20);
        glPopMatrix();
    //mouth3
        glColor3f(0.5, 1, 0);
        glPushMatrix();
        glTranslatef(32, 0, 0);
        glRotatef(-90, 0, 1, 0);
        gluCylinder(stemquad, 10, 20, 10, 20, 20);
        glPopMatrix();
    //mouth4
        glPushMatrix();
        glTranslatef(10, -5, 0);
        glScaled(1, 1, 1.5);
        gluSphere(stemquad, 25-mouthRadius*0.5, 20, 20);
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

void PeaShooter::animation(){
    if (getCooldownState() < 2 ) {
        if (mouthRadius > 4) {
            mouthRadius -= 1;
        }
        if (mouthLength > -5) {
            mouthLength -= 0.5;
        }
        if (getCooldownState() == 1 && angle < 30)
            angle += 1;
        if (getCooldownState() == 0 && angle < 30)
            angle += 1;
        
    }else if (getCooldownState() > 8){
        if (mouthRadius < 15) {
            mouthRadius += 1;
        }
        if (mouthLength < 0) {
            mouthLength += 0.5;
        }
        if (angle > -10) {
            angle -= 1;
        }
        
    }else {
        if (mouthRadius > 15) {
            mouthRadius--;
        } else if (mouthRadius < 15) {
            mouthRadius++;
        }
        
        if (mouthLength > 0) {
            mouthLength -= 0.5;
        } else if (mouthLength < 0) {
            mouthLength += 0.5;
        }
        
        if (angle > 0) {
            angle--;
        } else if (angle < 0) {
            angle++;
        }
        
    }
    

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