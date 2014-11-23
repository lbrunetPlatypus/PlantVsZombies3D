#include <cmath>
#include <iostream>
//#include <unistd.h>
#include "Sun.h"
#include "SunPlant.h"
#include "Zombie.h"
#include "PeaShooter.h"
#include "Gameboard.h"
#include "BoardSquare.h"
#include <stdlib.h>

#ifdef __APPLE__
#include "GLUT/glut.h"
#elif _WIN32
#include "Gl/glut.h"
#endif

#define PI 3.14159265

using namespace std;
GLint width=0,height=0;

static GLfloat Xangle = 5.0, Yangle = 0.0; // Angles to rotate
static GLfloat Z = 700.0; //position on Z-axis
static GLfloat windowWidth = 1000.0, windowHeight = 1000.0, windowNear = 1.0, windowFar = 4800.0, fovy = 90; //projection parameters

vector<Zombie> zombiesList;
Gameboard game(9,5);
Sun sun;
SunPlant sunplant;
Zombie zombie;
PeaShooter pea;

void display()
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    
    
    gluPerspective(fovy, windowWidth / windowHeight, windowNear, windowFar);

    gluLookAt(0, 100, Z, 0, 0, 0, 0, 1, 0); //position of the camera
    glRotatef(Xangle, 1.0, 0.0, 0.0); //rotation with up/down arrow key
    glRotatef(Yangle, 0.0, 1.0, 0.0); //rotation with left/right arrow key
    //glTranslatef(-xHelicopter, 0, -yHelicopter);
    
    
    glMatrixMode(GL_MODELVIEW);
    
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // Enable depth testing.
    
    glLoadIdentity();
    //glTranslatef(-200, 0, -200);
    
    //Centering the scene
	glTranslatef(-game.getSizeX()*BoardSquare::size / 2.0, 0, -game.getSizeZ()*BoardSquare::size / 2.0);

    
    //add a sun to the case 0
    game.addObject(&sun, 0);
    //add a sunplant to the case 1
    game.addObject(&sunplant, 1);
    //add a zombie to the case 2
    game.addObject(&zombie, 2);
    //add a peashooter to the case 3
    game.addObject(&pea, 3);

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

// OpenGL window reshape routine.
void reshape(int w, int h)
{
    width=w;
    height=h;
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
        default:
            break;
            
    }
    glutPostRedisplay();
}


void move(int value) {
    //cout << "je pop" << endl;
    //glutPostRedisplay();
    for (int i=0; i<game.getZombiesList().size(); i++) {
        game.getZombiesList().at(i)->move();
    }
    glutTimerFunc(500, move, 1);
    
}

void move2(int value) {
    //cout << "je te kill" << endl;
    //glutPostRedisplay();
    if (zombiesList.size() >0) {
        game.zombieSpawn(zombiesList.at(zombiesList.size()-1));
        zombiesList.pop_back();
        glutTimerFunc(5000, move2, 1);
    }
    
}

int main(int argc, char **argv)
{
    
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 600)/2,(glutGet(GLUT_SCREEN_HEIGHT) - 600)/2); //centering the window
    glutCreateWindow("Plant vs Zombie");
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    
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

