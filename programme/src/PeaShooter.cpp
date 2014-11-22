#include "PeaShooter.h"

PeaShooter::PeaShooter() {

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

void PeaShooter::draw() {
    glPushMatrix();
    glTranslatef(getPosition().getX(), getPosition().getY(), getPosition().getZ());
    glColor3f(0, 1, 1);
    gluSphere(gluNewQuadric(), 40, 20, 20);
    glPopMatrix();
}

Bullet PeaShooter::shoot() {
	Bullet bullet;
	return bullet;
}