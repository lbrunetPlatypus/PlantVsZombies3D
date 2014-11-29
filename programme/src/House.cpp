#include "House.h"
#include <math.h>


House::House(){
}

void House::draw(GLuint texture[], int length, int width, int height) {//texture 1=wall,2=window;3=door.
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[13]);
	//float angleRoof = atan2(2 * HeightRoof, width);
//length wall
	glPushMatrix();
	glTranslatef(-3*width/4 ,0,length/2);
	glRotatef(90, 0, 1, 0);
		glBegin(GL_QUADS);
			//length wall in the back
			//glTexCoord2f(0.5 + 0.5*cos(i*PI / 10)*cos(j * 2 * PI / 10), 0.5 + 0.5*cos(i*PI / 10)*sin(j * 2 * PI / 10));
        glTexCoord2f(1, 1);
		glVertex3f(-length / 2, height, -width / 2);
        glTexCoord2f(1,  0);
		glVertex3f(length / 2, height, -width / 2);
        glTexCoord2f(0, 0);
		glVertex3f(length / 2, 0, -width / 2);
        glTexCoord2f(0,  1);
		glVertex3f(-length / 2, 0, -width / 2);
    glEnd();
    glBegin(GL_QUADS);

		//length wall in front
		//glTexCoord2f(0.5 + 0.5*cos(i*PI / 10)*cos(j * 2 * PI / 10), 0.5 + 0.5*cos(i*PI / 10)*sin(j * 2 * PI / 10));
        glTexCoord2f(1,  0);
		glVertex3f(-length / 2, height, width / 2);
        glTexCoord2f(1, 1);
		glVertex3f(length / 2, height, width / 2);
        glTexCoord2f(0,  1);
		glVertex3f(length / 2, 0, width / 2);
        glTexCoord2f(0, 0);
		glVertex3f(-length / 2, 0, width / 2);
		
    glEnd();
    glBegin(GL_QUADS);

		//SideWall 
		//left
        glTexCoord2f(1,  0);
		glVertex3f(-length / 2, height, width / 2);
        glTexCoord2f(1, 1);
		glVertex3f(-length / 2, height, -width / 2);
        glTexCoord2f(0,  1);
		glVertex3f(-length / 2, 0, -width / 2);
        glTexCoord2f(0, 0);
		glVertex3f(-length / 2, 0, width / 2);
    glEnd();
    glBegin(GL_QUADS);
		//right
        glTexCoord2f(1,  0);
		glVertex3f(length / 2, height, width / 2);
        glTexCoord2f(1, 1);
		glVertex3f(length / 2, height, -width / 2);
        glTexCoord2f(0,  1);
		glVertex3f(length / 2, 0, -width / 2);
        glTexCoord2f(0, 0);
		glVertex3f(length / 2, 0, width / 2);
    
        glEnd();
        glBegin(GL_QUADS);

		//door at length wall/2, size = length/12 height=2height/3
		float doorZ = (width / 2) + 0.05;
		glColor3f(1, 0, 0);
		glVertex3f(-length / 12, 2*height/3, doorZ+1);
		glVertex3f(length / 12, 2 * height / 3, doorZ+1);
		glVertex3f(length / 12, 0, doorZ+1);
		glVertex3f(-length / 12, 0, doorZ+1);

		//windows
		float windowZ = (width / 2) + 0.05;
		float windowWidth = length / 8;
		float WindowPos = length / 3;
		glColor4f(0, 0, 1,0.5);
		glVertex3f(-WindowPos , 3* height / 4, windowZ+1);
		glVertex3f(-WindowPos+windowWidth, 3 * height / 4, windowZ+1);
		glVertex3f(-WindowPos + windowWidth, 1 * height / 4, windowZ+1);
		glVertex3f(-WindowPos, 1 * height / 4, windowZ+1);

		glVertex3f(WindowPos-windowWidth, 3 * height / 4, windowZ+1);
		glVertex3f(WindowPos, 3 * height / 4, windowZ+1);
		glVertex3f(WindowPos , 1 * height / 4, windowZ+1);
		glVertex3f(WindowPos - windowWidth, 1 * height / 4, windowZ+1);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, texture[12]);
    glBegin(GL_QUADS);

		//roof big side
		float roofHeight = height / 3;
        glColor4f(1, 0, 0,1);
    glTexCoord2f(1,  0);
		glVertex3f(-length / 2, height + roofHeight,0);
    glTexCoord2f(1, 1);
		glVertex3f(length / 2, height + roofHeight, 0);
    glTexCoord2f(0,  1);
		glVertex3f(length / 2, height, -width / 2);
    glTexCoord2f(0, 0);
		glVertex3f(-length / 2, height, -width / 2);

    glTexCoord2f(1,  0);
        glVertex3f(-length / 2, height + roofHeight, 0);
    glTexCoord2f(1, 1);
		glVertex3f(length / 2, height + roofHeight,0);
    glTexCoord2f(0,  1);
		glVertex3f(length / 2, height, width / 2);
    glTexCoord2f(0, 0);
		glVertex3f(-length / 2, height, width / 2);

		glEnd();
		

		// roof small side
		glBegin(GL_TRIANGLES);
    
    glTexCoord2f(0, 0);
	glVertex3f(-length / 2, height, width / 2);
    glTexCoord2f(0.5, 1);
		glVertex3f(-length / 2, height + roofHeight, 0);
    glTexCoord2f(0,  1);
		glVertex3f(-length / 2, height, -width / 2);
    glEnd();
    glBegin(GL_TRIANGLES);

    glTexCoord2f(0, 1);
		glVertex3f(length / 2, height, width / 2);
    glTexCoord2f(0, 0);
		glVertex3f(length / 2, height + roofHeight, 0);
    glTexCoord2f(1, 1);
		glVertex3f(length / 2, height, -width / 2);

		glEnd();

    glDisable(GL_TEXTURE_2D);

	glPopMatrix();







	/*
	glPushMatrix();
	glTranslatef(getPosition().getX(), 30, getPosition().getZ());
	glColor3f(1, 1, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	gluQuadricTexture(petalsquad, 1);
	//draw petals
	glPushMatrix();
	glTranslatef(0, 50, 0);
	glScalef(1, 0.7, 1);
	for (int i = 0; i<nPetals; i++) {
		glPushMatrix();
		glTranslatef(0, (sunRadius + petalLength / 2)*cos(i*(2 * PI / nPetals)), (sunRadius + petalLength / 2)*sin(i*(2 * PI / nPetals)));
		glRotatef(i*(360 / nPetals), 1, 0, 0);
		glScalef(5, petalLength, 2 * PI*sunRadius / nPetals / 1.5);
		gluSphere(petalsquad, 1, 20, 20);
		glPopMatrix();
	}



	glBindTexture(GL_TEXTURE_2D, texture[2]);
	gluQuadricTexture(flowerQuad, 1);

	glColor3f(1, 1, 1);

	glPushMatrix();
	glScalef(0.33, 1, 1);
	gluSphere(flowerQuad, sunRadius, 20, 20);
	glPopMatrix();


	glBindTexture(GL_TEXTURE_2D, texture[1]);
	gluQuadricTexture(stemquad, 1);
	glColor3f(0, 1, 0);

	glPushMatrix();
	glTranslatef(-5, 0, 0);
	glScalef(0.33, 1, 1);
	gluSphere(stemquad, sunRadius, 20, 20);
	glPopMatrix();



	glPopMatrix();
	glColor3f(0, 1, 0);

	glPushMatrix();
	glTranslatef(-10, 25, 0);
	glRotatef(90, 1, 0, 0);
	gluCylinder(stemquad, 5, 5, 50, 20, 20);
	glPopMatrix();


	//draw Leaves
	glPushMatrix();
	glScalef(1.5, 1, 1);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	gluQuadricTexture(leavesquad, 1);

	glTranslatef(-5, -25, 15);
	glRotatef(-90, 1, 0, 0);
	for (int i = 0; i<slices; i++) {
		for (int j = 0; j<stacks; j++) {
			glBegin(GL_QUADS);
			glTexCoord2f(0.5 + 0.5*cos(i*PI / 10)*cos(j * 2 * PI / 10), 0.5 + 0.5*cos(i*PI / 10)*sin(j * 2 * PI / 10));
			glVertex3f(r*cos((i)*PI / slices)*cos((j)* 2 * PI / stacks), 20 * cos((i)*PI / slices)*sin((j)* 2 * PI / stacks), r*sin((i)*PI / slices));
			glTexCoord2f(0.5 + 0.5*cos(i*PI / 10)*cos((j + 1) * 2 * PI / 10), 0.5 + 0.5*cos(i*PI / 10)*sin((j + 1) * 2 * PI / 10));
			glVertex3f(r*cos((i)*PI / slices)*cos((j + 1) * 2 * PI / stacks), 20 * cos((i)*PI / slices)*sin((j + 1) * 2 * PI / stacks), r*sin((i)*PI / slices));
			glTexCoord2f(0.5 + 0.5*cos((i + 1)*PI / 10)*cos((j + 1) * 2 * PI / 10), 0.5 + 0.5*cos((i + 1)*PI / 10) * 2 * sin((j + 1) * 2 * PI / 10));
			glVertex3f(r*cos((i + 1)*PI / slices)*cos((j + 1) * 2 * PI / stacks), 20 * cos((i + 1)*PI / slices)*sin((j + 1) * 2 * PI / stacks), r*sin((i + 1)*PI / slices));
			glTexCoord2f(0.5 + 0.5*cos((i + 1)*PI / 10)*cos(j * 2 * PI / 10), 0.5 + 0.5*cos((i + 1)*PI / 10)*sin(j * 2 * PI / 10));
			glVertex3f(r*cos((i + 1)*PI / slices)*cos((j)* 2 * PI / stacks), 20 * cos((i + 1)*PI / slices)*sin((j)* 2 * PI / stacks), r*sin((i + 1)*PI / slices));
			glEnd();
		}

	}
	glPopMatrix();

	glRotatef(90, 0, 1, 0);
	glPushMatrix();
	glScalef(1.5, 1, 1);

	glTranslatef(-5, -25, 15);
	glRotatef(-90, 1, 0, 0);
	for (int i = 0; i<slices; i++) {
		for (int j = 0; j<stacks; j++) {
			glBegin(GL_QUADS);
			glTexCoord2f(0.5 + 0.5*cos(i*PI / 10)*cos(j * 2 * PI / 10), 0.5 + 0.5*cos(i*PI / 10)*sin(j * 2 * PI / 10));
			glVertex3f(r*cos((i)*PI / slices)*cos((j)* 2 * PI / stacks), 20 * cos((i)*PI / slices)*sin((j)* 2 * PI / stacks), r*sin((i)*PI / slices));
			glTexCoord2f(0.5 + 0.5*cos(i*PI / 10)*cos((j + 1) * 2 * PI / 10), 0.5 + 0.5*cos(i*PI / 10)*sin((j + 1) * 2 * PI / 10));
			glVertex3f(r*cos((i)*PI / slices)*cos((j + 1) * 2 * PI / stacks), 20 * cos((i)*PI / slices)*sin((j + 1) * 2 * PI / stacks), r*sin((i)*PI / slices));
			glTexCoord2f(0.5 + 0.5*cos((i + 1)*PI / 10)*cos((j + 1) * 2 * PI / 10), 0.5 + 0.5*cos((i + 1)*PI / 10) * 2 * sin((j + 1) * 2 * PI / 10));
			glVertex3f(r*cos((i + 1)*PI / slices)*cos((j + 1) * 2 * PI / stacks), 20 * cos((i + 1)*PI / slices)*sin((j + 1) * 2 * PI / stacks), r*sin((i + 1)*PI / slices));
			glTexCoord2f(0.5 + 0.5*cos((i + 1)*PI / 10)*cos(j * 2 * PI / 10), 0.5 + 0.5*cos((i + 1)*PI / 10)*sin(j * 2 * PI / 10));
			glVertex3f(r*cos((i + 1)*PI / slices)*cos((j)* 2 * PI / stacks), 20 * cos((i + 1)*PI / slices)*sin((j)* 2 * PI / stacks), r*sin((i + 1)*PI / slices));
			glEnd();
		}
	}

	glPopMatrix();

	glRotatef(90, 0, 1, 0);
	glPushMatrix();
	glScalef(1.5, 1, 1);

	glTranslatef(-5, -25, 15);
	glRotatef(-90, 1, 0, 0);
	for (int i = 0; i<slices; i++) {
		for (int j = 0; j<stacks; j++) {
			glBegin(GL_QUADS);
			glTexCoord2f(0.5 + 0.5*cos(i*PI / 10)*cos(j * 2 * PI / 10), 0.5 + 0.5*cos(i*PI / 10)*sin(j * 2 * PI / 10));
			glVertex3f(r*cos((i)*PI / slices)*cos((j)* 2 * PI / stacks), 20 * cos((i)*PI / slices)*sin((j)* 2 * PI / stacks), r*sin((i)*PI / slices));
			glTexCoord2f(0.5 + 0.5*cos(i*PI / 10)*cos((j + 1) * 2 * PI / 10), 0.5 + 0.5*cos(i*PI / 10)*sin((j + 1) * 2 * PI / 10));
			glVertex3f(r*cos((i)*PI / slices)*cos((j + 1) * 2 * PI / stacks), 20 * cos((i)*PI / slices)*sin((j + 1) * 2 * PI / stacks), r*sin((i)*PI / slices));
			glTexCoord2f(0.5 + 0.5*cos((i + 1)*PI / 10)*cos((j + 1) * 2 * PI / 10), 0.5 + 0.5*cos((i + 1)*PI / 10) * 2 * sin((j + 1) * 2 * PI / 10));
			glVertex3f(r*cos((i + 1)*PI / slices)*cos((j + 1) * 2 * PI / stacks), 20 * cos((i + 1)*PI / slices)*sin((j + 1) * 2 * PI / stacks), r*sin((i + 1)*PI / slices));
			glTexCoord2f(0.5 + 0.5*cos((i + 1)*PI / 10)*cos(j * 2 * PI / 10), 0.5 + 0.5*cos((i + 1)*PI / 10)*sin(j * 2 * PI / 10));
			glVertex3f(r*cos((i + 1)*PI / slices)*cos((j)* 2 * PI / stacks), 20 * cos((i + 1)*PI / slices)*sin((j)* 2 * PI / stacks), r*sin((i + 1)*PI / slices));
			glEnd();
		}
	}

	glPopMatrix();
	glRotatef(90, 0, 1, 0);

	glPushMatrix();
	glScalef(1.5, 1, 1);

	glTranslatef(-5, -25, 15);
	glRotatef(-90, 1, 0, 0);
	for (int i = 0; i<slices; i++) {
		for (int j = 0; j<stacks; j++) {
			glBegin(GL_QUADS);
			glTexCoord2f(0.5 + 0.5*cos(i*PI / 10)*cos(j * 2 * PI / 10), 0.5 + 0.5*cos(i*PI / 10)*sin(j * 2 * PI / 10));
			glVertex3f(r*cos((i)*PI / slices)*cos((j)* 2 * PI / stacks), 20 * cos((i)*PI / slices)*sin((j)* 2 * PI / stacks), r*sin((i)*PI / slices));
			glTexCoord2f(0.5 + 0.5*cos(i*PI / 10)*cos((j + 1) * 2 * PI / 10), 0.5 + 0.5*cos(i*PI / 10)*sin((j + 1) * 2 * PI / 10));
			glVertex3f(r*cos((i)*PI / slices)*cos((j + 1) * 2 * PI / stacks), 20 * cos((i)*PI / slices)*sin((j + 1) * 2 * PI / stacks), r*sin((i)*PI / slices));
			glTexCoord2f(0.5 + 0.5*cos((i + 1)*PI / 10)*cos((j + 1) * 2 * PI / 10), 0.5 + 0.5*cos((i + 1)*PI / 10) * 2 * sin((j + 1) * 2 * PI / 10));
			glVertex3f(r*cos((i + 1)*PI / slices)*cos((j + 1) * 2 * PI / stacks), 20 * cos((i + 1)*PI / slices)*sin((j + 1) * 2 * PI / stacks), r*sin((i + 1)*PI / slices));
			glTexCoord2f(0.5 + 0.5*cos((i + 1)*PI / 10)*cos(j * 2 * PI / 10), 0.5 + 0.5*cos((i + 1)*PI / 10)*sin(j * 2 * PI / 10));
			glVertex3f(r*cos((i + 1)*PI / slices)*cos((j)* 2 * PI / stacks), 20 * cos((i + 1)*PI / slices)*sin((j)* 2 * PI / stacks), r*sin((i + 1)*PI / slices));
			glEnd();
		}
	}

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	*/
}