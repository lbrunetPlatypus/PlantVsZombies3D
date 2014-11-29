#include <cmath>
#include <iostream>
#include "Sun.h"
#include "SunPlant.h"
#include "Zombie.h"
#include "PeaShooter.h"
#include "Gameboard.h"
#include "BoardSquare.h"
#include "getbmp.h"
#include "House.h"

#define COOLDOWN 10;
#define SUN_COOLDOWN 20;

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
static GLenum wireShaded = GL_FILL; //wired or shaded
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
int sunCooldown = 0;
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
//House
House house;
//animation
float animPos = 0;
float deltaAnimMove = 0.5;
float plantAnimPos=5;
float deltaPlantAnimMove = 1;
float density = 0.001;

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

//write a string on the viewport
void writeBitmapString(string string)
{
    for (int i=0; i<string.length() ; i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
    }
}

void drawPlayerViewport(){
    glViewport(0, 9*height/10, width, height/10);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, 1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0, 0, 0);
    if (game.isGameover()) {
        glRasterPos2d(0, 0);
        writeBitmapString("GAME OVER !!");
    } else {
        glRasterPos2d(-1, 0);
        writeBitmapString("Plant selection :");
        if (plantSelection == 1) {
            glPushMatrix();
                glTranslatef(-0.4, -1, 0);
                glScalef(1.0/(9*height/10), 10.0/(9*height/10), 1.0/(9*height/10));
                PeaShooter peashooter;
                peashooter.draw(texture,0);
            glPopMatrix();
        }
        else if (plantSelection == 2){
            glPushMatrix();
                glTranslatef(-0.4, -1, 0);
                glScalef(1.0/(9*height/10), 10.0/(9*height/10), 1.0/(9*height/10));
                SunPlant sunplant;
                glRotatef(-90, 0, 1, 0);
				sunplant.draw(texture, 0);
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
            zombie.draw(texture, 0);
        glPopMatrix();
        writeBitmapString(" X " + std::to_string(game.getZombiesList().size() + zombiesList.size()));
    }
    glPopMatrix();
    
}

// OpenGL window reshape routine.
void reshape(int w, int h)
{
    width = w;
    height = h;
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

void Normal( GLfloat p0[], GLfloat p1[], GLfloat p2[], GLfloat n[]) {
    float x3, y3, z3, x4, y4, z4; //t: (x3, y3, z3), r: (x4, y4, z4)
    x3 = p1[0] - p0[0]; y3 = p1[1] - p0[1]; z3 = p1[2] - p0[2]; //t=P1-P0
    x4 = p2[0] - p0[0]; y4 = p2[1] - p0[1]; z4 = p2[2] - p0[2]; //r=P2-P0
    // n = t x r. ‘x is the cross-product. u is perpendicular to the plane
    n[0] = y3*z4 - y4*z3; n[1] = -(x3*z4 - x4*z3); n[2] = x3*y4 - x4*y3;
}

void callLight() {
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
    GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat position[] = { 0, 1, 0, 0.0 };  /* Infinite light location. */
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void drawFloor() {
    GLfloat length =6000;
    GLint nbMesh =100/2;
    
    GLfloat x=0.0, y=0.0, increment = 1;
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[10]);
    for (int j=0; j<2*nbMesh; j++) {
        if (y>=1.0) {
            y=0.0;
        }
        
        glColor3f(1, 1, 1);
        for (int i=0; i<2*nbMesh; i++) {
            GLfloat p1[] = {-length + i*length/nbMesh, -1, -length + j*length/nbMesh};
            GLfloat p2[] = {-length + i*length/nbMesh, -1, -length + (j+1)*length/nbMesh};
            GLfloat p3[] = {-length + (i+1)*length/nbMesh, -1, -length + j*length/nbMesh};
            GLfloat p4[] = {-length + (i+1)*length/nbMesh, -1, -length + (j+1)*length/nbMesh};
            GLfloat n1[3], n2[3];
            
            Normal(p1, p2, p3, n1);
            Normal(p4, p3, p2, n2);
            
            glNormal3f(n1[0], n1[1], n1[2]);
            glBegin(GL_TRIANGLES);
            glTexCoord2f(x, y);
            glVertex3f(p1[0], p1[1], p1[2]);
            glTexCoord2f(x, y+increment);
            glVertex3f(p2[0], p2[1], p2[2]);
            glTexCoord2f(x+increment, y);
            glVertex3f(p3[0], p3[1], p3[2]);
            glEnd();
            glNormal3f(n2[0], n2[1], n2[2]);
            glBegin(GL_TRIANGLES);
            glTexCoord2f(x, y+increment);
            glVertex3f(p2[0], p2[1], p2[2]);
            glTexCoord2f(x+increment, y);
            glVertex3f(p3[0], p3[1], p3[2]);
            glTexCoord2f(x+increment, y+increment);
            glVertex3f(p4[0], p4[1], p4[2]);
            glEnd();
            
            x += increment;
        }
        y += increment;
    }
    glDisable(GL_TEXTURE_2D);
    
}

//draw scene
void drawScene() {
    //draw the panoramique view = environment.
    GLUquadric* spherequad = gluNewQuadric();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[11]);
    gluQuadricTexture(spherequad,1);
    
    glColor3f(1, 1, 1);
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
        gluSphere(spherequad, 3000, 100, 100);
        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
    drawFloor();
    
}


void display()
{

    glViewport(0, 0, width, 9*height/10);

	
	//change density to change fog thickness
	

	GLuint filter;                      // Which Filter To Use
	GLuint fogMode[] = { GL_EXP, GL_EXP2, GL_LINEAR };   // Storage For Three Types Of Fog
	GLuint fogfilter = 0;                    // Which Fog To Use
	GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };      // Fog Color

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);          // We'll Clear To The Color Of The Fog ( Modified )

	glFogi(GL_FOG_MODE, fogMode[fogfilter]);        // Fog Mode
	glFogfv(GL_FOG_COLOR, fogColor);            // Set Fog Color
	glFogf(GL_FOG_DENSITY,density);              // How Dense Will The Fog Be
	glHint(GL_FOG_HINT, GL_DONT_CARE);          // Fog Hint Value
	glFogf(GL_FOG_START, 1.0f);             // Fog Start Depth
	glFogf(GL_FOG_END, 5.0f);               // Fog End Depth
	glEnable(GL_FOG);                   // Enables GL_FOG

	

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glPushMatrix();
		gluPerspective(fovy, windowWidth / windowHeight, windowNear, windowFar);
		glMatrixMode(GL_MODELVIEW);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST); // Enable depth testing.
        glPolygonMode(GL_FRONT_AND_BACK, wireShaded);
		glLoadIdentity();
    //Centering the scene
		glTranslatef(translationX, translationY, translationZ);
		gluLookAt(camPosX, camPosY, camPosZ, lookAtX, lookATY, lookAtZ, 0, 1, 0); //position of the camera
		glRotatef(Xangle, 1.0, 0.0, 0.0); //rotation with up/down arrow key
		glRotatef(Yangle, 0.0, 1.0, 0.0); //rotation with left/right arrow key
		glTranslatef(-game.getSizeX()*BoardSquare::size / 2.0, 0, -game.getSizeZ()*BoardSquare::size / 2.0);
    //draw the scene with its component.
        callLight();
        if (wireShaded == GL_FILL) {
            drawScene();
        }
		DrawGrid();
		game.draw(texture, animPos, plantAnimPos);
    glPopMatrix();
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
    loadExternalTextures("/Users/Xiang/Documents/Concordia/COMP 371 - Computer Graphics/Plant vs Zombie/PlantVsZombies3D/programme/img/floor.bmp", texture[10]);
    loadExternalTextures("/Users/Xiang/Documents/Concordia/COMP 371 - Computer Graphics/Plant vs Zombie/PlantVsZombies3D/programme/img/sky.bmp", texture[11]);
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
    loadExternalTextures("..\\..\\img\\floor.bmp", texture[10]);
    loadExternalTextures("..\\..\\img\\sky.bmp", texture[11]);
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
            if (Xangle < 90) {
                Xangle += 5.0f;
            }
            break;
        case GLUT_KEY_DOWN :	// Rotate on y axis
            if (Xangle > 0) {
                Xangle -= 5.0f;
            }
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
		case 'f':
			if (density<0.005)
			density += 0.001;
			break;
		case 'F':
			if (density>0)
			density -= 0.001;
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
        case 'w':
            if(wireShaded == GL_FILL)
                wireShaded = GL_LINE;
            else
                wireShaded = GL_FILL;
            
            break;
        default:
            
            break;
            
    }
    glutPostRedisplay();
}


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
				if (currentHoveredSquare != -1){
                    if (plantSelection == 1 && nbSun>=nbSunPeaShooter) {
                        if (game.addPlant(&peaShootersList[compteurPlant], currentHoveredSquare)) {;
                            compteurPlant += 1;
                            nbSun -= nbSunPeaShooter;
                        }
                    }
                    else if (plantSelection ==2 && nbSun>=nbSunSunFlower) {
                        if (game.addPlant(&sunPlantsList[compteurPlant], currentHoveredSquare)) {;
                            compteurPlant += 1;
                            nbSun -= nbSunSunFlower;
                        }
                    }
					else if (plantSelection == 0){
						nbSun += game.selectSun();
					}
					
				}
                _mouseLeft = true;
                break;
            case GLUT_MIDDLE_BUTTON:
                _mouseMiddle = true;
                break;
            case GLUT_RIGHT_BUTTON:
                _mouseRight = true;
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
    
	if (_mouseMiddle) {
		//zoomIn/out
		translationZ += -dy;
		changed = true;
	}
	if (_mouseRight) {//on rotate autour de l'obj
		Yangle += dx;
		Xangle += dy;
		changed = true;
    }
    _mouseX = x;
    _mouseY = y;
    
    
    if (changed) {
        glutPostRedisplay();
    }
}

void mousePassiveFunc(int x, int y)
{
	game.checkSunHoveringStatus(x, y);
	currentHoveredSquare = game.checkSquareHoveringStatus(x, y);
}

void plantAnim(int value){
	plantAnimPos += deltaPlantAnimMove;
	//to keep animPos in the intervall [0,4]
	if (plantAnimPos >= 20 || animPos <= 0){
		deltaPlantAnimMove = -deltaPlantAnimMove;
	}

	glutTimerFunc(200, plantAnim, 1);

}


void move(int value) {
	
	animPos += deltaAnimMove;
	//to keep animPos in the intervall [0,4]
	if (animPos >= 3|| animPos <= 0){
		deltaAnimMove = -deltaAnimMove;
	}
	



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
    
    if ( sunCooldown == 0) {
        game.produceSun(Position(rand()%game.getSizeX()*50, 0, rand()%game.getSizeZ()*50));
        sunCooldown = SUN_COOLDOWN;
    }
    else {
        sunCooldown--;
    }
    
   game.UpdatePlants();
    
    glutTimerFunc(500, move2, 1);
    
}

int main(int argc, char **argv)
{
    for (int i=0; i<50; i++) {
        peaShootersList.push_back(PeaShooter());
    }
    
    for (int i=0; i<50; i++) {
        sunPlantsList.push_back(SunPlant());
    }
    
    for (int i=0; i<30; i++) {
        Zombie zombie;
        zombiesList.push_back(zombie);
    }

	game.setHouse(house);
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

    
    
    move(1);
    move2(1);
	plantAnim(1);
    
    setup();
    
    glutMainLoop();
}
