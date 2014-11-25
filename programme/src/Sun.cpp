#include "Sun.h"

Sun::Sun() {
    despawn = 50;
}

int Sun::getDespawn(){
    return despawn;
}

void  Sun::setDespawn(int _despawn){
	despawn = _despawn;
}

void Sun::update() {
    despawn--;
}

float Sun::getScreenCoordX(){
	return Sun::screenCoordX;
}
float Sun::getScreenCoordY(){
	return Sun::screenCoordY;
}
void Sun::setScreencoordX(float _screenCoordX){
	screenCoordX = _screenCoordX;
}
void Sun::setScreencoordY(float _screenCoordY){
	screenCoordY = _screenCoordY;
}

bool Sun::getIsHovered(){
	return Sun::isHovered;
}
void Sun::setIsHovered(bool status){
	isHovered = status;
}

void Sun::draw(GLuint texture[]) {
    glPushMatrix();
    glTranslatef(getPosition().getX(), getPosition().getY(), getPosition().getZ());
    glTranslatef(0, 20, 0);
	if (getIsHovered())
		glColor3f(0.7, 0.7, 0);
	else
        glColor3f(1, 1, 0);
    gluSphere(gluNewQuadric(), 20, 20, 20);
    glPopMatrix();
}