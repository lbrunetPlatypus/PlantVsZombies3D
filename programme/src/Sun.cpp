#include "Sun.h"

Sun::Sun() {
}

void Sun::draw() {
    glPushMatrix();
    glTranslatef(getPosition().getX(), getPosition().getY(), getPosition().getZ());
    glColor3f(1, 1, 0);
    gluSphere(gluNewQuadric(), 40, 20, 20);
    glPopMatrix();
}