#include <cmath>
#include <iostream>
#include "Sun.h"
#include "SunPlant.h"
#include "Zombie.h"
#include "PeaShooter.h"
#include "Gameboard.h"
#include "BoardSquare.h"

#ifdef __APPLE__
#include "GLUT/glut.h"
#elif _WIN32
#include "Gl/glut.h"
#endif

#define PI 3.14159265

using namespace std;
GLint width=0,height=0;

static GLfloat Xangle = 5.0, Yangle = 0.0; // Angles to rotate
static GLfloat translationX ;
static GLfloat translationY;
static GLfloat translationZ; //to zoom in/out the scene

//static GLfloat Z = 700.0; //position on Z-axis
static GLfloat windowWidth = 1000.0, windowHeight = 1000.0, windowNear = 1.0, windowFar = 4800.0, fovy = 90; //projection parameters
double _left = 0.0;		/* ortho view volume params */
double _right = 0.0;
double _bottom = 0.0;
double _top = 0.0;

vector<Zombie> zombiesList;
vector<Bullet*> bulletsList;
Gameboard game(9,5);
Sun sun;
SunPlant sunplant;
Zombie zombie;
PeaShooter pea;
Bullet bullet;

// Plants table
vector<PeaShooter> peaShootersList;
vector<SunPlant> sunPlantsList;
int plantSelection = 0;

// Player Info


//Camera Position
static GLfloat camPosX = 0;
static GLfloat camPosY = 100;
static GLfloat camPosZ = 700.0; //position on Z-axis
static GLfloat lookAtX = 0;
static GLfloat lookATY = 0;
static GLfloat lookAtZ = 0; //position on Z-axis
//Model matrices
double _matrix[16];
double _matrixI[16];
/* Mouse Interface  */
int _mouseX = 0;		/* mouse control variables */
int _mouseY = 0;
bool _mouseLeft = false;
bool _mouseMiddle = false;
bool _mouseRight = false;

double _dragPosX = 0.0;
double _dragPosY = 0.0;
double _dragPosZ = 0.0;
double rotAngle = 0;

bool updatePos = false;
double prevMousePosx;
double prevMousePosy;
bool mouseInit = false;

//
//void invertMatrix(const GLdouble * m, GLdouble * out)
//{
//
//	/* NB. OpenGL Matrices are COLUMN major. */
//#define MAT(m,r,c) (m)[(c)*4+(r)]
//
//	/* Here's some shorthand converting standard (row,column) to index. */
//#define m11 MAT(m,0,0)
//#define m12 MAT(m,0,1)
//#define m13 MAT(m,0,2)
//#define m14 MAT(m,0,3)
//#define m21 MAT(m,1,0)
//#define m22 MAT(m,1,1)
//#define m23 MAT(m,1,2)
//#define m24 MAT(m,1,3)
//#define m31 MAT(m,2,0)
//#define m32 MAT(m,2,1)
//#define m33 MAT(m,2,2)
//#define m34 MAT(m,2,3)
//#define m41 MAT(m,3,0)
//#define m42 MAT(m,3,1)
//#define m43 MAT(m,3,2)
//#define m44 MAT(m,3,3)
//
//	GLdouble det;
//	GLdouble d12, d13, d23, d24, d34, d41;
//	GLdouble tmp[16];		/* Allow out == in. */
//
//	/* Inverse = adjoint / det. (See linear algebra texts.) */
//
//	/* pre-compute 2x2 dets for last two rows when computing */
//	/* cofactors of first two rows. */
//	d12 = (m31 * m42 - m41 * m32);
//	d13 = (m31 * m43 - m41 * m33);
//	d23 = (m32 * m43 - m42 * m33);
//	d24 = (m32 * m44 - m42 * m34);
//	d34 = (m33 * m44 - m43 * m34);
//	d41 = (m34 * m41 - m44 * m31);
//
//	tmp[0] = (m22 * d34 - m23 * d24 + m24 * d23);
//	tmp[1] = -(m21 * d34 + m23 * d41 + m24 * d13);
//	tmp[2] = (m21 * d24 + m22 * d41 + m24 * d12);
//	tmp[3] = -(m21 * d23 - m22 * d13 + m23 * d12);
//
//	/* Compute determinant as early as possible using these cofactors. */
//	det = m11 * tmp[0] + m12 * tmp[1] + m13 * tmp[2] + m14 * tmp[3];
//
//	/* Run singularity test. */
//	if (det == 0.0) {
//		/* printf("invert_matrix: Warning: Singular matrix.\n"); */
//		/* 	  memcpy(out,_identity,16*sizeof(double)); */
//	}
//	else {
//		GLdouble invDet = 1.0 / det;
//		/* Compute rest of inverse. */
//		tmp[0] *= invDet;
//		tmp[1] *= invDet;
//		tmp[2] *= invDet;
//		tmp[3] *= invDet;
//
//		tmp[4] = -(m12 * d34 - m13 * d24 + m14 * d23) * invDet;
//		tmp[5] = (m11 * d34 + m13 * d41 + m14 * d13) * invDet;
//		tmp[6] = -(m11 * d24 + m12 * d41 + m14 * d12) * invDet;
//		tmp[7] = (m11 * d23 - m12 * d13 + m13 * d12) * invDet;
//
//		/* Pre-compute 2x2 dets for first two rows when computing */
//		/* cofactors of last two rows. */
//		d12 = m11 * m22 - m21 * m12;
//		d13 = m11 * m23 - m21 * m13;
//		d23 = m12 * m23 - m22 * m13;
//		d24 = m12 * m24 - m22 * m14;
//		d34 = m13 * m24 - m23 * m14;
//		d41 = m14 * m21 - m24 * m11;
//
//		tmp[8] = (m42 * d34 - m43 * d24 + m44 * d23) * invDet;
//		tmp[9] = -(m41 * d34 + m43 * d41 + m44 * d13) * invDet;
//		tmp[10] = (m41 * d24 + m42 * d41 + m44 * d12) * invDet;
//		tmp[11] = -(m41 * d23 - m42 * d13 + m43 * d12) * invDet;
//		tmp[12] = -(m32 * d34 - m33 * d24 + m34 * d23) * invDet;
//		tmp[13] = (m31 * d34 + m33 * d41 + m34 * d13) * invDet;
//		tmp[14] = -(m31 * d24 + m32 * d41 + m34 * d12) * invDet;
//		tmp[15] = (m31 * d23 - m32 * d13 + m33 * d12) * invDet;
//
//		memcpy(out, tmp, 16 * sizeof(GLdouble));
//	}
//
//#undef m11
//#undef m12
//#undef m13
//#undef m14
//#undef m21
//#undef m22
//#undef m23
//#undef m24
//#undef m31
//#undef m32
//#undef m33
//#undef m34
//#undef m41
//#undef m42
//#undef m43
//#undef m44
//#undef MAT
//}
//
//double vlen(double x, double y, double z)
//{
//	return sqrt(x * x + y * y + z * z);
//}
//
void pos(double *px, double *py, double *pz, const int x, const int y,
         const int *viewport)
{
    /*
     Use the ortho projection and viewport information
     to map from mouse co-ordinates back into world
     co-ordinates
     */
    
    *px = (double)(x - viewport[0]) / (double)(viewport[2]);
    *py = (double)(y - viewport[1]) / (double)(viewport[3]);
    
    *px = _left + (*px) * (_right - _left);
    *py = _top + (*py) * (_bottom - _top);
    *pz = windowNear;
    windowWidth = 1000.0, windowHeight = 1000.0, windowNear = 1.0, windowFar = 4800.0, fovy = 90;
}

// OpenGL window reshape routine.
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    _top = 1.0;
    _bottom = -1.0;
    _left = -(double)w / (double)h;
    _right = -_left;
    
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /* glOrtho(_left,_right,_bottom,_top,_zNear,_zFar);  Ortho */
    gluPerspective(fovy, (double)w / (double)h, windowNear, windowFar);	/* PErspective for stereo */
    
    glMatrixMode(GL_MODELVIEW);
    width = w;
    height = h;
}

void display()
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, windowWidth / windowHeight, windowNear, windowFar);
    
    
    
    
    glMatrixMode(GL_MODELVIEW);
    
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // Enable depth testing.
    
    glLoadIdentity();
    //glTranslatef(-200, 0, -200);
    //Centering the scene
    
    glTranslatef(translationX, translationY, translationZ);
    
    gluLookAt(camPosX, camPosY, camPosZ, lookAtX, lookATY, lookAtZ, 0, 1, 0); //position of the camera
    //glPushMatrix();
    //glTranslatef(-translationX, -translationY, -translationZ);
    glRotatef(Xangle, 1.0, 0.0, 0.0); //rotation with up/down arrow key
    glRotatef(Yangle, 0.0, 1.0, 0.0); //rotation with left/right arrow key
    glTranslatef(-game.getSizeX()*BoardSquare::size / 2.0, 0, -game.getSizeZ()*BoardSquare::size / 2.0);
    //glTranslatef(translationX, translationY, translationZ);
    //glPopMatrix();
    
    //glTranslatef(-xHelicopter, 0, -yHelicopter);
    //draw the scene with its component.
    game.draw();
    
    //game.getSunList().at(game.getSunList().size()-1).draw();
    
    
    
    
    
    
    glDisable(GL_DEPTH_TEST); // Disable depth testing.
    
    
    glFlush();
    glutSwapBuffers();
    
}

void setup(void)
{
    
    glClearColor (1, 1, 1, 0.0);
    
}




void specialKey(int key, int x, int y) {
    switch (key) {
            
        case GLUT_KEY_LEFT :    // Rotate on x axis
            Yangle -= 5.0f;
            break;
        case GLUT_KEY_RIGHT :	// Rotate on x axis
            Yangle += 5.0f;
            break;
        case GLUT_KEY_UP :		// Rotate on y axis
            Xangle += 5.0f;
            break;
        case GLUT_KEY_DOWN :	// Rotate on y axis
            Xangle -= 5.0f;
            break;
    }
    glutPostRedisplay();		// Redraw the scene
}


void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27:
            exit(0);
            break;
        case 's': {
            sunPlantsList.push_back(SunPlant());
            int square;
            game.addPlant(&sunPlantsList[plantSelection], plantSelection);
            break;}
        case 'p': {
            peaShootersList.push_back(PeaShooter());
            int square;
            game.addPlant(&peaShootersList[plantSelection], plantSelection);
            plantSelection++;
            break;}
        default:
            
            break;
            
    }
    glutPostRedisplay();
}
//
//void getMatrix()
//{
//	glGetDoublev(GL_MODELVIEW_MATRIX, _matrix);
//	invertMatrix(_matrix, _matrixI);
//}

void Mouse(int button, int state, int x, int y)
{
    _mouseX = x;
    _mouseY = y;
    if (state == GLUT_UP)//if no mouse input
    {
        switch (button) {
            case GLUT_LEFT_BUTTON:
                _mouseLeft = false;
                break;
            case GLUT_MIDDLE_BUTTON:
                _mouseMiddle = false;
                break;
            case GLUT_RIGHT_BUTTON:
                _mouseRight = false;
                break;
                /*case 4:         //Zoomout
                 glLoadIdentity();
                 glTranslatef(0, 0, -0.1);
                 glMultMatrixd(_matrix);
                 //getMatrix();
                 std::cout << "scroll back" << std::endl;
                 glutPostRedisplay();
                 break;
                 case 3:         //Zoomin
                 glLoadIdentity();
                 glTranslatef(0, 0, 0.1);
                 glMultMatrixd(_matrix);
                 //getMatrix();
                 std::cout << "scroll in" << std::endl;
                 glutPostRedisplay();
                 break;*/
        }
    }
    else{//if mouse input
        switch (button) {
            case GLUT_LEFT_BUTTON:
                //Collect sun or plant preselected plant
                _mouseLeft = true;
                //std::cout << "mouse left" << std::endl;
                break;
            case GLUT_MIDDLE_BUTTON:
                _mouseMiddle = true;
                //std::cout << "mouse middle" << std::endl;
                break;
            case GLUT_RIGHT_BUTTON:
                _mouseRight = true;
                //	std::cout << "mouse right" << std::endl;
                break;
                
            default:
                break;
        }
    }
}



void mouseMoveEvent(int x, int y)
{
    
    bool changed = false;
    
    const int dx = x - _mouseX;
    const int dy = y - _mouseY;
    
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    
    if (dx == 0 && dy == 0)
        return;
    
    if (_mouseMiddle ) {
        //zoomIn/out
        translationZ+= dy;
        changed = true;
    }
    if (_mouseRight) {//on rotate autour de l'obj
        Yangle += dx;
        changed = true;
    }
    //move the scene
    /*else if (_mouseLeft) {//move the scene
     
     double px, py, pz;
     
     pos(&px, &py, &pz, x, y, viewport);//goto mouse coordinate to world coordinate
     //	//px, py, pz mouse position in the world coordinate
     
     //	glLoadIdentity();
     //	glTranslatef(px - _dragPosX, py - _dragPosY, pz - _dragPosZ);
     //	glMultMatrixd(_matrix);
     translationX += (px - _dragPosX)*100;
     translationY += (py - _dragPosY)*100;
     translationZ += (pz - _dragPosZ)*100 ;
     _dragPosX = px;
     _dragPosY = py;
     _dragPosZ = pz;
     //std::cout << _dragPosX << "   " << _dragPosY << "   " << _dragPosZ << std::endl;
     changed = true;
     }*/
    
    _mouseX = x;
    _mouseY = y;
    
    
    if (changed) {
        //getMatrix();
        glutPostRedisplay();
    }
}

void mousePassiveFunc(int x, int y)
{
    //std::cout <<"mouse   " << y << std::endl;
    game.checkSunHoveringStatus(x, y);
}

void move(int value) {
    //cout << "je pop" << endl;
    //glutPostRedisplay();
    game.UpdateZombies();
    game.UpdateSuns();
    
    game.UpdateBullets();
    glutTimerFunc(100, move, 1);
    
}

void move2(int value) {
    //cout << "je te kill" << endl;
    //glutPostRedisplay();
    if (zombiesList.size() >0) {
        game.zombieSpawn(zombiesList.at(zombiesList.size()-1));
        zombiesList.pop_back();
    }
    
    game.UpdatePlants();
    
    glutTimerFunc(1000, move2, 1);
    
}

int main(int argc, char **argv)
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 600)/2,(glutGet(GLUT_SCREEN_HEIGHT) - 600)/2); //centering the window
    glutCreateWindow("Plant vs Zombie");
    
    translationX = 0;
    translationY = 0;
    translationZ = -game.getSizeZ()*BoardSquare::size / 2.0; //to zoom in/out the scene
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(Mouse);
    //glutMouseWheelFunc(MouseWheel);
    glutMotionFunc(mouseMoveEvent);
    glutPassiveMotionFunc(mousePassiveFunc);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    
    //add a sun to the case 0
    // game.addObject(&sun, 35);
    //add a sunplant to the case 1
    
    //game.addPlant(&sunplant, 38);
    //add a peashooter to the case 3
    //game.addPlant(&pea, 1);
    //game.addPea(1);
    PeaShooter pea1, pea2, pea3, pea4, pea5;
    
    
    //pea.setGameboard(&game);
    
    for (int i=0; i<100; i++) {
        peaShootersList.push_back(PeaShooter());
    }
    
    for (int i=0; i<100; i++) {
        sunPlantsList.push_back(SunPlant());
    }
    
    for (int i=0; i<10; i++) {
        Zombie zombie;
        zombiesList.push_back(zombie);
    }
    
    
    game.produceSun(Position(100,0,200));
    
    
    move(1);
    move2(1);
    
    setup();
    
    glutMainLoop();
}
