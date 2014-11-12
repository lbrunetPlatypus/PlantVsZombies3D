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

Bullet shoot() {
	Bullet bullet;
	return bullet;
}