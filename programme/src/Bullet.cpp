#include "Bullet.h"

void Bullet::draw() {
    glPushMatrix();
    glTranslatef(getPosition().getX(), getPosition().getY(), getPosition().getZ());
    glColor3f(0.6, 0.6, 0);
    gluSphere(gluNewQuadric(), 10, 20, 20);
    glPopMatrix();
}

void Bullet::move() {
    Position position = getPosition();
    if (getPosition().getX()>0)
        position = position + Position(-1, 0, 0);
    setPosition(position);
    glutPostRedisplay();
}

