//
//  corn.c
//  lab_week01
//
//  Created by JoJo on 2015. 8. 31..
//  Copyright (c) 2015년 JoJo. All rights reserved.
//

#include <stdio.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <math.h>

#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void RenderScene()
{
	GLfloat x,y,angle;
	int iPivot = 1; // add
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    
	glBegin(GL_TRIANGLE_FAN); // add
	glVertex3f(0.0f, 0.0f, 75.0f); // add - 기준점
	for(angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f))
	{
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
		if((iPivot %2) == 0) // add
			glColor3f((float)254/255, (float)173/255, (float)158/255);
		else
			glColor3f((float)175/255, (float)240/255, (float)220/255);
		iPivot++;
		glVertex2f(x, y);
	}
	glEnd();
    
	glBegin(GL_TRIANGLE_FAN); // add
	glVertex2f(0.0f, 0.0f); // add - 기준점
	for(angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f))
	{
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
		if((iPivot %2) == 0)    // add
			glColor3f((float)254/255, (float)173/255, (float)158/255);
		else
			glColor3f((float)175/255, (float)240/255, (float)220/255);
		iPivot++;
		glVertex2f(x, y);
	}
	glEnd();
    
	glPopMatrix();
	glutSwapBuffers();
}
void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	glColor3f(0.0f, 1.0f, 0.0f);
	glShadeModel(GL_FLAT); // add
	glFrontFace(GL_CW); //
}

void KeyControl(int key, int x, int y)
{
    if(key == GLUT_KEY_UP)
        xRot -=5.0f;
    if(key == GLUT_KEY_DOWN)
        xRot +=5.0f;
    if(key == GLUT_KEY_LEFT)
        yRot -=5.0f;
    if(key == GLUT_KEY_RIGHT)
        yRot +=5.0f;
    glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
    GLfloat nRange = 100.0f;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w ,h );
    if(w<=h)
        glOrtho(-nRange,nRange,-
                nRange*h/w,nRange*h/w,-nRange, nRange);
    else
        glOrtho(-nRange*w/h,nRange*w/h,-
                nRange,nRange,-nRange, nRange);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1500, 1000);
	glutCreateWindow("SpringVertex");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
    
}
