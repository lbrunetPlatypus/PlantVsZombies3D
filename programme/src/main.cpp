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
Bullet bullet, temp;

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
    glTranslatef(-game.getSizeX()*BoardSquare::size/2.0, 0, -game.getSizeZ()*BoardSquare::size/2.0);
    
    
    //draw the scene with its component.
	
    game.draw();
    
    int j=0;
    while (!bullet.checkCollision(*game.getZombiesList().at(j)) && j<game.getZombiesList().size()-1 ) {
        j++;
    }
    if (j<game.getZombiesList().size()-1) {
        bullet = Bullet();
        cout << "touche !" << endl;
    }else {
        bullet.draw();
    }
    
    
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

void Mouse(int button, int state, int x, int y)
{
		if (state == GLUT_UP)//if no mouse input
			switch (button) {
			case GLUT_LEFT_BUTTON:

				//_mouseLeft = false;
				break;
			case GLUT_MIDDLE_BUTTON:
				//_mouseMiddle = false;
				break;
			case GLUT_RIGHT_BUTTON:
				//_mouseRight = false;
				break;
		}
		else//if mouse input
			switch (button) {
			case GLUT_LEFT_BUTTON:
				//Collect sun or plant preselected plant
				std::cout << "left click" << std::endl;
				//_mouseLeft = true;
				break;
			case GLUT_MIDDLE_BUTTON:
				std::cout << "middle click" << std::endl;
				//_mouseMiddle = true;
				break;
			case GLUT_RIGHT_BUTTON:
				std::cout << "right click" << std::endl;
				//_mouseRight = true;
				break;
			case 4:         //Zoomout
				/*glLoadIdentity();
				glTranslatef(0, 0, -0.1);
				glMultMatrixd(_matrix);
				getMatrix();*/
				std::cout << "scroll back" << std::endl;
				glutPostRedisplay();
				break;
			case 3:         //Zoomin
				/*glLoadIdentity();
				glTranslatef(0, 0, 0.1);
				glMultMatrixd(_matrix);
				getMatrix();*/
				std::cout << "scroll in" << std::endl;
				glutPostRedisplay();
				break;
			default:
				break;
		}
}

void move(int value) {
    //cout << "je pop" << endl;
    //glutPostRedisplay();
  /*  for (int i=0; i<game.getZombiesList().size(); i++) {
        game.getZombiesList().at(i)->move();
    }*/
	game.UpdateZombies();
    if (bullet.getPosition().getX() != 0 && bullet.getPosition().getZ()!=0) {
        bullet.move();
        
    }
    glutTimerFunc(100, move, 1);
    
}

void move2(int value) {
    //cout << "je te kill" << endl;
    //glutPostRedisplay();
    if (zombiesList.size() >0) {
        game.zombieSpawn(zombiesList.at(zombiesList.size()-1));
        
        
        zombiesList.pop_back();
    }
    temp = ((PeaShooter*)game.getSquaresList().at(3).getObject())->shoot();
    if (temp.getPosition().getX()!=0 && temp.getPosition().getZ() != 0) {
        bullet = temp;
    }
    glutTimerFunc(1000, move2, 1);
    
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
	glutMouseFunc(Mouse);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    
    //add a sun to the case 0
    game.addObject(&sun, 35);
    //add a sunplant to the case 1
	game.addObject(&sunplant, 36);
    //add a peashooter to the case 3
    game.addObject(&pea, 3);
    
    pea.setGameboard(&game);
    
	
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

