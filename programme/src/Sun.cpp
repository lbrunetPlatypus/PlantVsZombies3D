#include "Sun.h"

Sun::Sun() {
    despawn = 50;
}

int Sun::getDespawn(){
    return despawn;
}

void Sun::update() {
    despawn--;
}

void Sun::draw() {
    glPushMatrix();
    glTranslatef(getPosition().getX(), getPosition().getY(), getPosition().getZ());
    glTranslatef(0, 20, 0);
    glColor3f(1, 1, 0);
    gluSphere(gluNewQuadric(), 20, 20, 20);
    glPopMatrix();
}