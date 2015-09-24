//
//  pp5.c
//  lab_week01
//
//  Created by JoJo on 2015. 9. 23..
//  Copyright (c) 2015년 JoJo. All rights reserved.
//

#include <stdio.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <math.h>
#include "SOIL.h"

#define GL_PI 3.14159f
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zDistance = 0.0f;

GLfloat amb [] = { 0.5f, 0.5f, 0.5f, 1.0f};
GLfloat dif [] = { 0.8f, 0.8f, 0.8f, 1.0f};
GLfloat	lightPos[] = { -50.0f, 50.0f, 100.0f, 1.0f};

GLuint tex;
GLfloat theta = GL_PI / 8;
GLfloat alpha = GL_PI / 4;

void gltDrawSphere(GLfloat fRadius, GLint iSlices, GLint iStacks)
{
    GLfloat drho = (GLfloat)(3.141592653589) / (GLfloat) iStacks;
    GLfloat dtheta = 2.0f * (GLfloat)(3.141592653589) / (GLfloat) iSlices;
	GLfloat ds = 1.0f / (GLfloat) iSlices;
	GLfloat dt = 1.0f / (GLfloat) iStacks;
	GLfloat t = 1.0f;
	GLfloat s = 0.0f;
    GLint i, j;     // Looping variables
    
	for (i = 0; i < iStacks; i++)
    {
		GLfloat rho = (GLfloat)i * drho;
		GLfloat srho = (GLfloat)(sin(rho));
		GLfloat crho = (GLfloat)(cos(rho));
		GLfloat srhodrho = (GLfloat)(sin(rho + drho));
		GLfloat crhodrho = (GLfloat)(cos(rho + drho));
        
        // Many sources of OpenGL sphere drawing code uses a triangle fan
        // for the caps of the sphere. This however introduces texturing
        // artifacts at the poles on some OpenGL implementations
		glBegin(GL_TRIANGLE_STRIP);
        s = 0.0f;
		for ( j = 0; j <= iSlices; j++)
        {
			GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;
			GLfloat stheta = (GLfloat)(-sin(theta));
			GLfloat ctheta = (GLfloat)(cos(theta));
            
			GLfloat x = stheta * srho;
			GLfloat y = ctheta * srho;
			GLfloat z = crho;
            
            glTexCoord2f(s, t);
            glNormal3f(x, y, z);
            glVertex3f(x * fRadius, y * fRadius, z * fRadius);
            
            x = stheta * srhodrho;
			y = ctheta * srhodrho;
			z = crhodrho;
			glTexCoord2f(s, t - dt);
            s += ds;
            glNormal3f(x, y, z);
            glVertex3f(x * fRadius, y * fRadius, z * fRadius);
        }
        glEnd();
        
        t -= dt;
    }
}


void SetupRC()
{
	glEnable(GL_DEPTH_TEST);
    
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0,GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0,GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT0,GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    glEnable(GL_TEXTURE_2D);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}



void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
    glRotatef(xRot, 10.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f,0.0f, zDistance);
    
    
    tex = SOIL_load_OGL_texture("resources/donut.jpg", SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // 얼굴 그리기
    glColor3ub(236, 206, 50);
    glutSolidSphere(6, 40, 40);
    
    // 코 그리기
    glTranslatef(0.0f, -1.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 6.0f);
    glColor3ub(216, 82, 19);
    glutSolidSphere(0.8, 40, 40);
    glPopMatrix();
    
    
    // 수염 그리기
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 6.0f);
    glScalef(1.1f, 1.0f, 0.4f);
    glColor3ub(232, 200, 39);
    glPushMatrix();
    
    // 왼쪽 수염
    glTranslatef(-1.0f, 0.0f, 0.0f);
    glutSolidSphere(1.5, 40, 40);
    
    // 오른쪽 수염
    glPopMatrix();
    glTranslatef(1.0f, 0.0f, 0.0f);
    glutSolidSphere(1.5, 40, 40);
    glPopMatrix();
    
    
    // 눈 그리기
    glPushMatrix();
    glTranslatef(0.0f, 1.5f, 5.5f);
    glScalef(1.0f, 1.0f, 0.2f);
    glColor3ub(0, 0, 0);
    glPushMatrix();
    
    // 왼쪽 눈
    glTranslatef(-2.8f, 0.0f, 0.0f);
    glutSolidSphere(0.5, 40, 40);
    
    // 오른쪽 눈
    glPopMatrix();
    glTranslatef(2.8f, 0.0f, 0.0f);
    glutSolidSphere(0.5, 40, 40);
    glPopMatrix();
    
    
    // 갈기 그리기
    glTranslatef(0.0f, 1.0f, 0.0f);
    for (int i=0; i<8; i++) {
        glPushMatrix();
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTranslatef((6+4.5)*cos(theta+i*alpha), (6+4.5)*sin(theta+i*alpha), 0.0f);
        glColor3f(1.0f, 1.0f, 0.0f);
        gltDrawSphere(4.5, 40, 40);
        glPopMatrix();
    }
    
    
    
    glPopMatrix();
    glPopMatrix();
    
	glutSwapBuffers();
}

void KeyControl(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;
    
	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;
    
	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;
    
	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;
    
	if(key == GLUT_KEY_HOME)
		zDistance += 5.0f;
    
	if(key == GLUT_KEY_END)
		zDistance -= 5.0f;
    
	glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
	GLfloat fAspect;
    
	glViewport(0,0,w,h);
	fAspect = (GLfloat)w/(GLfloat)h;
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
	gluPerspective(45.0f,fAspect,1.0f,500.0f);
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-50.0f);
    
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("pp5");
	glutSpecialFunc(KeyControl);
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
    
	SetupRC();
	glutMainLoop();
	
}
