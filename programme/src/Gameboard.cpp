#include "Gameboard.h"


Gameboard::Gameboard(){

}

Gameboard::Gameboard(int _sizeX,int _sizeZ){
	sizeX = _sizeX;
	sizeZ = _sizeZ;
	int id = -1;
	for (int i = 0; i < _sizeX; i++){
		for (int j = 0; j < _sizeZ; j++){
			id++;
			BoardSquare tempSquare = BoardSquare(i, j, id );
			squaresList.push_back(tempSquare);
		}
	}

}

void Gameboard::addObject(GameObject object,int squareId){
	//set object position using the square?
	squaresList[squareId].setObject(object);
	
}

void Gameboard::deleteObject(int squareId){

}

void Gameboard::UpdateScreenCoordinate()
{
	/*GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLdouble winX, winY, winZ;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	for (unsigned i = 0; i<squaresList.size(); i++)
	{
		double mm[16];
		//mult(modelview, joints[i].global_t, mm);

		gluProject((GLdouble)squaresList[i].get2DPosition().getX(), squaresList[i].get2DPosition().getY(), (GLdouble)squaresList[i].get2DPosition().getZ(),
			modelview, projection, viewport,
			&winX, &winY, &winZ);
		squaresList[i].setScreenCoordinateX(winX);
		squaresList[i].setScreenCoordinateY((double)glutGet(GLUT_WINDOW_HEIGHT) - winY) ;
	}*/
	
}

void Gameboard::checkHoveringStatus(int x, int y)//x, y being the mouse position on screen
{
	double distance = 0.0f;
	double minDistance = 1000.0f;
	int hoveredSquare = -1;
	for (unsigned i = 0; i < squaresList.size(); i++)
	{
		squaresList[i].setHoveringStatus(false);
		distance = sqrt((x - squaresList[i].getScreenCoordinate().x)*(x - squaresList[i].getScreenCoordinate().y)
			+ (y - squaresList[i].getScreenCoordinate().y)*(y - squaresList[i].getScreenCoordinate().y));
		if (distance > 50) continue;
		if (distance < minDistance)
		{
			hoveredSquare = i;
			minDistance = distance;
		}
	}
	if (hoveredSquare != -1) squaresList[hoveredSquare].setHoveringStatus(true);
}

const Vec3 operator + (const Vec3& v1, const Vec3& v2){
	return Vec3(v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z);
}
const Vec3 operator * (const Vec3& v1, const double& coeff){
	return Vec3(v1.x*coeff,
		v1.y*coeff,
		v1.z*coeff);
}
const Vec3 operator - (const Vec3& v1, const Vec3& v2){
	return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}
