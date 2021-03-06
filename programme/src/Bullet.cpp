#include "Bullet.h"

void Bullet::draw(GLuint texture[]) {
    glPushMatrix();
    glTranslatef(getPosition().getX(), getPosition().getY(), getPosition().getZ());
    glColor3f(0.6, 0.6, 0);
    gluSphere(gluNewQuadric(), 10, 20, 20);
    glPopMatrix();
}

void Bullet::move() {
    Position position = getPosition();
    position = position + Position(15, 0, 0);
    setPosition(position);
    glutPostRedisplay();
}

bool Bullet::checkCollision(Zombie& zombie){
    if (getPosition().getZ() == zombie.getPosition().getZ()) {
        if (getPosition().getX() < zombie.getPosition().getX()) {
            return false;
        }
        else {
            zombie.takeDamages(10);
            return true;
        }
    }
    else {
        return false;
    }
}

