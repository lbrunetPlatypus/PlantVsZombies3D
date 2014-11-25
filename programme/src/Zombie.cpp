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
        {0,1,2,3}, // front
        {1,0,5,4}, // bottom
        {4,0,6,2}, // left
        {1,5,3,7}, // right
        {7,6,3,2}, // top
        {5,4,7,6} // back
    };
    
    GLfloat n[3];
    
    GLint texture[4][2]{
        {0,0},
        {1,0},
        {0,1},
        {1,1}
    };
    glScalef(size, size, size);
    for (int i=0; i<6; i++) {
        glBegin(GL_TRIANGLES);
        for (int j=0; j<3; j++) {
            glTexCoord2d(texture[j][0], texture[j][1]);
            glVertex3f(p[faces[i][j]][0],p[faces[i][j]][1],p[faces[i][j]][2]);
        }
        glEnd();
        glBegin(GL_TRIANGLES);
        for (int j=1; j<4; j++) {
            glTexCoord2d(texture[j][0], texture[j][1]);
            glVertex3f(p[faces[i][j]][0],p[faces[i][j]][1],p[faces[i][j]][2]);
        }
        glEnd();
    }
    glPopMatrix();
    
}

Zombie::Zombie() {
    hp = 100;
    attackPoint = 10;
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

void Zombie::nibble(Plant& plant, int nbDamages){//makedamages to the objet in front
    if (coolDownState == 0) {
        coolDownState = coolDown;
        plant.ApplyDamages(nbDamages);
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
    
    glPushMatrix();
        glTranslatef(getPosition().getX(), getPosition().getY(), getPosition().getZ());
        glTranslatef(0, 100, 0);

        //head
        glPushMatrix();
        glColor3f(0.35, 0.42, 0.34);
        gluSphere(gluNewQuadric(), 15, 20, 20);
        glPopMatrix();
        
        //torso
        glColor3f(0.36, 0.20, 0.09);
        glTranslatef(0, 5, 0);
        glPushMatrix();
            glTranslatef(0, -40, 0);
            glScalef(1, 2, 1);
            drawCube(20);
        glPopMatrix();
        
        
        //RIGHT - leg + foot
        glColor3f(0.23, 0.35, 0.58);
        glPushMatrix();
            glTranslatef(0, -80, -6);
    
            glPushMatrix();
                glScalef(1, 4, 1);
                drawCube(10);
            glPopMatrix();
    
            glTranslatef(-5, -20, 0);
            glScalef(2, 1, 1);
            glColor3f(0.36, 0.20, 0.09);
            drawCube(10);
        glPopMatrix();
        
        //LEFT - leg + foot
        glColor3f(0.23, 0.35, 0.58);

        glPushMatrix();
            glTranslatef(0, -80, 6);
    
            glPushMatrix();
                glScalef(1, 4, 1);
                drawCube(10);
            glPopMatrix();
    
            glTranslatef(-5, -20, 0);
            glScalef(2, 1, 1);
            glColor3f(0.36, 0.20, 0.09);
            drawCube(10);
        glPopMatrix();
        
        //RIGHT - arm + hand
        glPushMatrix();
            glTranslatef(-20, -25, -20);
    
            glPushMatrix();
                glScalef(3, 1, 1);
                glColor3f(0.36, 0.20, 0.09);
                drawCube(10);
            glPopMatrix();
    
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

    
    glPopMatrix();
}

