#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Position.h"

#ifdef __APPLE__
#include "GLUT/glut.h"
#elif _WIN32
#include "Gl/glut.h"
#endif

class Gameboard;

class GameObject {
    
    private :
    Position position;
    Gameboard* gameboard;
    
    public :
    GameObject();
    void setPosition(Position newPosition);
	Position getPosition();
    Gameboard* getGameboard();
    void setGameboard(Gameboard* _gameboard);
    virtual void draw(GLuint texture[]);
};

struct Vec3
{
	double x, y, z;
	Vec3() { x = 0; y = 0; z = 0; }
	Vec3(double a, double b, double c) :x(a), y(b), z(c){}
};

const Vec3 operator + (const Vec3& v1, const Vec3& v2);
const Vec3 operator - (const Vec3& v1, const Vec3& v2);
const Vec3 operator * (const Vec3& v1, const double& coeff);


#endif