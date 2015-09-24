//
//  spring.c
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


void RenderScene(void)
{
	
	GLfloat x, y, z, angle;
	glClear(GL_COLOR_BUFFER_BIT);
	
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	
	glBegin(GL_POINTS);
	z = -50.0f;
    
	for (angle = 0.0f; angle <= (2.0f*GL_PI)*3.0f; angle += 0.1f)
	{
		x = 60.0f*sin(angle);
		x = 60.0f*cos(angle);
		glVertex3f(x, y, z);
		z += 0.5f;
	}
	glEnd();
	glPopMatrix();
	glutSwapBuffers();
	
}

void Keycontrol(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;
	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;
	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;
	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;
    
	glutPostRedisplay();
}

void SetupRC(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat nRange = 100.0f;
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
    
	if (w <= h)
	{
		glOrtho(-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
	}
	else
	{
		glOrtho(-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("SpringVertex");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(Keycontrol);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
    return 0;
    
}

