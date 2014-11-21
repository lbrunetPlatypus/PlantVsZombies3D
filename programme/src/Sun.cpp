#include "Sun.h"

Sun::Sun() {
}

void Sun::draw() {
    glPushMatrix();
    glColor3f(1, 1, 0);
    gluSphere(gluNewQuadric(), 100, 20, 20);
    glPopMatrix();
}