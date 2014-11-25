#include "Zombie.h"
#include "iostream"

void drawCube(int size) {
    glPushMatrix();
    GLfloat p[8][3] =
    {
        {-0.5, -0.5, -0.5},
        {0.5, -0.5, -0.5},
        {-0.5, 0.5, -0.5},
        {0.5, 0.5, -0.5},
        {-0.5, -0.5, 0.5},
        {0.5, -0.5, 0.5},
        {-0.5, 0.5, 0.5},
        {0.5, 0.5, 0.5}
    };
    
    GLint faces[6][4] {
        {4,0,2,6}, // left
        {0,1,3,2}, // front
        {1,5,7,3}, // right
        {5,4,6,7}, // back
        {1,0,4,5}, // bottom
        {7,6,2,3} // top
    };
    
    GLfloat n[3];
    
    GLint texture[4][2]{
        {0,0},
        {1,0},
        {1,1},
        {0,1}
    };
    glScalef(size, size, size);
    for (int i=0; i<6; i++) {
        //glBegin(GL_TRIANGLES);
        glBegin(GL_QUADS);
        for (int j=0; j<4; j++) {
            if (i<4)
            glTexCoord2d(i/4.0+texture[j][0]/4.0, texture[j][1]);
            glVertex3f(p[faces[i][j]][0],p[faces[i][j]][1],p[faces[i][j]][2]);
        }
        glEnd();
    }
    glPopMatrix();
    
}

Zombie::Zombie() {
    hp = 100;
    attackPoint = 3;
    speed = 5;
    coolDown = 5;
    coolDownState = 0;
}

int Zombie::getHp() {
    return hp;
}

int Zombie::getAttackPoint() {
    return attackPoint;
}

int Zombie::getSpeed() {
    return speed;
}

int Zombie::getCooldown() {
    return coolDown;
}

int Zombie::getCooldownState() {
    return coolDownState;
}

void Zombie::setCooldown(int _cooldown){
    coolDown = _cooldown;
}

void Zombie::setCooldownState(int _cooldownState) {
    coolDownState = _cooldownState;
}

bool Zombie::detectTarget(Plant& plant){
	
	if (getPosition().getZ() == plant.getPosition().getZ()) {
		if (getPosition().getX() > plant.getPosition().getX()) {
			return false;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
	 return true;
}

void Zombie::move(){
    Position position = getPosition();
    if (getPosition().getX()>0)
    position = position + Position(-1, 0, 0);
    setPosition(position);
    glutPostRedisplay();
}

void Zombie::nibble(Plant& plant){//makedamages to the objet in front
    if (coolDownState == 0) {
        coolDownState = coolDown;
        plant.ApplyDamages(attackPoint);
    }else {
        coolDownState--;
    }
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

void Zombie::draw(GLuint texture[]) {

    GLUquadric* zombieface = gluNewQuadric();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    gluQuadricTexture(zombieface,1);

    glPushMatrix();
        glTranslatef(getPosition().getX(), getPosition().getY(), getPosition().getZ());
        glTranslatef(0, 100, 0);

        //head
        glPushMatrix();
        glColor3f(1, 1, 1);
        glRotatef(-90, 1, 0, 0);

        glRotatef(-90, 0, 0, 1);
        gluSphere(zombieface, 15, 20, 20);
        glPopMatrix();
    
    
        //torso
    glBindTexture(GL_TEXTURE_2D, texture[5]);

        glTranslatef(0, 5, 0);
        glPushMatrix();
            glTranslatef(0, -40, 0);
            glScalef(1, 2, 1);
            drawCube(20);
        glPopMatrix();

    
    glBindTexture(GL_TEXTURE_2D, texture[6]);

        //RIGHT - arm + hand
        glPushMatrix();
            glTranslatef(-20, -25, -20);
    
            glPushMatrix();
                glScalef(3, 1, 1);
                glRotatef(-90, 0, 0, 1);

                drawCube(10);
            glPopMatrix();
    glDisable(GL_TEXTURE_2D);

            glColor3f(0.35, 0.42, 0.34);
            glTranslatef(-20, 0, 0);
            drawCube(10);
        glPopMatrix();


        //LEFT - arm + hand
        glPushMatrix();
            glTranslatef(-20, -25, 20);
    
            glPushMatrix();
                glScalef(3, 1, 1);
                glColor3f(0.36, 0.20, 0.09);
                drawCube(10);
            glPopMatrix();
    
            glColor3f(0.35, 0.42, 0.34);
            glTranslatef(-20, 0, 0);
            drawCube(10);
        glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[8]);
    //RIGHT - leg + foot
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0, -80, -6);
    
    glPushMatrix();
    glScalef(1, 4, 1);
    drawCube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glTranslatef(-5, -20, 0);
    glScalef(2, 1, 1);
    glColor3f(0.36, 0.20, 0.09);
    drawCube(10);
    glPopMatrix();
    
    //LEFT - leg + foot
    glColor3f(1, 1, 1);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[7]);
    
    glPushMatrix();
    glTranslatef(0, -80, 6);
    
    glPushMatrix();
    glScalef(1, 4, 1);
    drawCube(10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glTranslatef(-5, -20, 0);
    glScalef(2, 1, 1);
    glColor3f(0.36, 0.20, 0.09);
    drawCube(10);
    glPopMatrix();

    
    glPopMatrix();
}

