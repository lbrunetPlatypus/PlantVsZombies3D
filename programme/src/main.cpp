#include <cmath>
#include <iostream>
#include "Sun.h"
#include "SunPlant.h"
#include "Zombie.h"
#include "PeaShooter.h"
#include "Gameboard.h"
#include "BoardSquare.h"
#include "getbmp.h"

#define COOLDOWN 5;

#ifdef __APPLE__
#include "GLUT/glut.h"
#elif _WIN32
#include "Gl/glut.h"
#endif
#define PI 3.14159265
using namespace std;

//window /projection infos
GLint width=0,height=0;
static GLfloat windowWidth = 1000.0, windowHeight = 1000.0, windowNear = 1.0, windowFar = 4800.0, fovy = 90; //projection parameters
double _left = 0.0;		/* ortho view volume params */
double _right = 0.0;
double _bottom = 0.0;
double _top = 0.0;
//Camera Position
static GLfloat camPosX = 0;
static GLfloat camPosY = 100;
static GLfloat camPosZ = 700.0; //position on Z-axis
static GLfloat lookAtX = 0;
static GLfloat lookATY = 0;
static GLfloat lookAtZ = 0; //position on Z-axis
//Camera movement
static GLfloat Xangle = 5.0, Yangle = 0.0; // Angles to rotate
static GLfloat translationX;
static GLfloat translationY;
static GLfloat translationZ; //to zoom in/out the scene
//Game info
vector<Zombie> zombiesList; //list of zombie to spawn
int spawnCooldown = COOLDOWN;
Gameboard game(9,5);
static int nbSunPeaShooter = 100;
static int nbSunSunFlower = 50;
static int currentHoveredSquare = -1;
// Plants table
vector<PeaShooter> peaShootersList;
vector<SunPlant> sunPlantsList;
int compteurPlant = 0;
int plantSelection = 0; //1 for peas 2 for sun
// Player Info
static int nbSun = 100;

/* Mouse Interface  */
int _mouseX = 0;		/* mouse control variables */
int _mouseY = 0;
bool _mouseLeft = false;
bool _mouseMiddle = false;
bool _mouseRight = false;

//textures !
GLuint texture[15];

//// Read a texture map from a BMP bitmap file.
void loadExternalTextures(string file, GLuint &texture)
{
    BitMapFile *image;
    image = getbmp(file);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->sizeX, image->sizeY, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
}
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
//write a string on the viewport
void writeBitmapString(string string)
{
    for (int i=0; i<string.length() ; i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
    }
}

void drawPlayerViewport(){
    string fps = "player score";
    glViewport(0, 9*height/10, width, height/10);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, 1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0, 0, 0);
    glRasterPos2d(-1, 0);
    writeBitmapString("Plant selection :");
    if (plantSelection == 1) {
        glPushMatrix();
            glTranslatef(-0.4, -1, 0);
            glScalef(1.0/(9*height/10), 10.0/(9*height/10), 1.0/(9*height/10));
            PeaShooter peashooter;
            peashooter.draw(texture);
        glPopMatrix();
    }
    else if (plantSelection == 2){
        glPushMatrix();
            glTranslatef(-0.4, -1, 0);
            glScalef(1.0/(9*height/10), 10.0/(9*height/10), 1.0/(9*height/10));
            SunPlant sunplant;
            glRotatef(-90, 0, 1, 0);
            sunplant.draw(texture);
        glPopMatrix();
    }
    glColor3f(0, 0, 0);
    glRasterPos2d(0, 0);
    writeBitmapString("Sun : " + std::to_string(nbSun));
    glRasterPos2f(0.5, 0);
    glPushMatrix();
        glTranslatef(0.4, -1, 0);
        glScalef(1.0/(9*height/10), 10.0/(9*height/10), 1.0/(9*height/10));
        Zombie zombie;
        glRotatef(180, 0, 1, 0);
        zombie.draw(texture);
    glPopMatrix();
    writeBitmapString(" X " + std::to_string(game.getZombiesList().size() + zombiesList.size()));
    glPopMatrix();
    
}

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
    width = w;
    height = h;
}

void worldAxis(){
	//world coordinate system Axis shown at (10,10,10)
	glPushMatrix();
	glTranslatef(0, 3, 0);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0.0);			// red for x axis
	glVertex3f(0, 0, 0);
	glVertex3f(600, 0, 0);
	glColor3f(0, 1, 0.0);				// green for y axis
	glVertex3f(0, 0, 0);
	glVertex3f(0, 600, 0);
	glColor3f(0.0, 0.0, 1.0);				// Blue for z axis
	glVertex3f(0, 0, 600);
	glEnd();
	glPopMatrix();
}
void DrawGrid()
{
	glBegin(GL_LINES);
	glColor3f(0.75f, 0.75f, 0.75f);
	for (int i = 0; i <= game.getSizeX(); i++)
	{
		glVertex3f((float)i * 100, 0, 0);
		glVertex3f((float)i * 100, 0, game.getSizeZ() * 100);
	}
	for (int i = 0; i <= game.getSizeZ(); i++)
	{
		glVertex3f(0, 0, (float)i * 100);
		glVertex3f(game.getSizeX() * 100, 0, (float)i * 100);
	}
	glEnd();
}

void display()
{
	std::cout <<"__________nbSun    "<< nbSun << std::endl;
    glViewport(0, 0, width, 9*height/10);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    glPushMatrix();

    gluPerspective(fovy, windowWidth / windowHeight, windowNear, windowFar);
    
    
    
    
    glMatrixMode(GL_MODELVIEW);
    
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); // Enable depth testing.
    
    glLoadIdentity();
    //glTranslatef(-200, 0, -200);
    //Centering the scene
	glPushMatrix();
	worldAxis();
	glPopMatrix();
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

	DrawGrid();
    game.draw(texture);
    glPopMatrix();
    
    //game.getSunList().at(game.getSunList().size()-1).draw();
    
    
    
    
    glDisable(GL_DEPTH_TEST); // Disable depth testing.

    drawPlayerViewport();

    
    glFlush();
	
    glutSwapBuffers();
    
}

void setup(void)
{
    
#ifdef __APPLE__
    loadExternalTextures("/Users/Xiang/Documents/Concordia/COMP 371 - Computer Graphics/Plant vs Zombie/PlantVsZombies3D/programme/img/leaves.bmp", texture[0]);
    loadExternalTextures("/Users/Xiang/Documents/Concordia/COMP 371 - Computer Graphics/Plant vs Zombie/PlantVsZombies3D/programme/img/stem.bmp", texture[1]);
    loadExternalTextures("/Users/Xiang/Documents/Concordia/COMP 371 - Computer Graphics/Plant vs Zombie/PlantVsZombies3D/programme/img/coeur.bmp", texture[2]);
    loadExternalTextures("/Users/Xiang/Documents/Concordia/COMP 371 - Computer Graphics/Plant vs Zombie/PlantVsZombies3D/programme/img/petals.bmp", texture[3]);
    loadExternalTextures("/Users/Xiang/Documents/Concordia/COMP 371 - Computer Graphics/Plant vs Zombie/PlantVsZombies3D/programme/img/zombieface.bmp", texture[4]);
    loadExternalTextures("/Users/Xiang/Documents/Concordia/COMP 371 - Computer Graphics/Plant vs Zombie/PlantVsZombies3D/programme/img/zombiebody.bmp", texture[5]);
    loadExternalTextures("/Users/Xiang/Documents/Concordia/COMP 371 - Computer Graphics/Plant vs Zombie/PlantVsZombies3D/programme/img/zombiearm.bmp", texture[6]);
    loadExternalTextures("/Users/Xiang/Documents/Concordia/COMP 371 - Computer Graphics/Plant vs Zombie/PlantVsZombies3D/programme/img/zombieleg.bmp", texture[7]);
    loadExternalTextures("/Users/Xiang/Documents/Concordia/COMP 371 - Computer Graphics/Plant vs Zombie/PlantVsZombies3D/programme/img/zombieleg2.bmp", texture[8]);
    loadExternalTextures("/Users/Xiang/Documents/Concordia/COMP 371 - Computer Graphics/Plant vs Zombie/PlantVsZombies3D/programme/img/stem1.bmp", texture[9]);
#elif _WIN32
    loadExternalTextures("..\\..\\img\\leaves.bmp", texture[0]);
    loadExternalTextures("..\\..\\img\\stem.bmp", texture[1]);
    loadExternalTextures("..\\..\\img\\coeur.bmp", texture[2]);
    loadExternalTextures("..\\..\\img\\petals.bmp", texture[3]);
    loadExternalTextures("..\\..\\img\\zombieface.bmp", texture[4]);
    loadExternalTextures("..\\..\\img\\zombiebody.bmp", texture[5]);
    loadExternalTextures("..\\..\\img\\zombiearm.bmp", texture[6]);
    loadExternalTextures("..\\..\\img\\zombieleg.bmp", texture[7]);
    loadExternalTextures("..\\..\\img\\zombieleg2.bmp", texture[8]);
    loadExternalTextures("..\\..\\img\\stem1.bmp", texture[9]);
#endif

    
    glClearColor (1, 1, 1, 0.0);
    glShadeModel(GL_SMOOTH);
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

//press a key
void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27:
            exit(0);
            break;
        case '1':
            plantSelection=1 ;
            break;
        case '2':
            plantSelection=2;
            break;
        default:
            
            break;
            
    }
    glutPostRedisplay();
}

//release a key
void keyboardUp (unsigned char key, int x, int y) {
    switch(key)
    {
        case '1':
            plantSelection=0;
            break;
        case '2':
            plantSelection=0;
            break;
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

			
				//std::cout << currentHoveredSquare << std::endl;
				//Collect sun or plant preselected plant
				
				if (currentHoveredSquare != -1){
					//std::cout << "click"<< std::endl;
                    if (plantSelection == 1 && nbSun>=nbSunPeaShooter) {
                        game.addPlant(&peaShootersList[compteurPlant], currentHoveredSquare);
                        compteurPlant += 1;
						nbSun -= nbSunPeaShooter;
						
						//std::cout << compteurPlant << std::endl;
                    }
                    else if (plantSelection ==2 && nbSun>=nbSunSunFlower) {
                        game.addPlant(&sunPlantsList[compteurPlant], currentHoveredSquare);
                        compteurPlant += 1;
						nbSun -= nbSunSunFlower;
                    }
					else if (plantSelection == 0){
						nbSun += game.selectSun();
					}
					
				}
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
	//glRotatef(-Yangle, 0.0, 1.0, 0.0); //rotation with left/right arrow key
	//glRotatef(-Xangle, 1.0, 0.0, 0.0); //rotation with up/down arrow key
	//glTranslatef(-translationX, -translationY, -translationZ);
	game.checkSunHoveringStatus(x, y);
	currentHoveredSquare = game.checkSquareHoveringStatus(x, y);

}


void move(int value) {

    game.UpdateZombies();
    game.UpdateSuns();
    
    game.UpdateBullets();
    glutTimerFunc(100, move, 1);
    
}

void move2(int value) {
    if (zombiesList.size() >0 && spawnCooldown == 0) {
        game.zombieSpawn(zombiesList.at(zombiesList.size()-1));
        zombiesList.pop_back();
        spawnCooldown = COOLDOWN;
    }
    else {
        spawnCooldown--;
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
	glutPassiveMotionFunc(mousePassiveFunc);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(Mouse);
    //glutMouseWheelFunc(MouseWheel);
    glutMotionFunc(mouseMoveEvent);
   
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialKey);
    
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    for (int i=0; i<100; i++) {
        peaShootersList.push_back(PeaShooter());
    }
    
    for (int i=0; i<100; i++) {
        sunPlantsList.push_back(SunPlant());
    }
    
    for (int i=0; i<30; i++) {
        Zombie zombie;
        zombiesList.push_back(zombie);
    }
    
    
    game.produceSun(Position(100,0,200));
    
    
    move(1);
    move2(1);
    
    setup();
    
    glutMainLoop();
}
