#include "Sun.h"

Sun::Sun() {
}

void Sun::draw() {
    glPushMatrix();
    glTranslatef(getPosition().getX(), getPosition().getY(), getPosition().getZ());
    glTranslatef(0, 20, 0);
    glColor3f(1, 1, 0);
    gluSphere(gluNewQuadric(), 20, 20, 20);
    glPopMatrix();
}