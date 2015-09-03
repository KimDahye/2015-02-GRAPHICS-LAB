//
//  pp1.c
//  lab_week01
//
//  Created by JoJo on 2015. 9. 2..
//  Copyright (c) 2015년 JoJo. All rights reserved.
//

#include <stdio.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

GLfloat x = 0.0f;
GLfloat y = 0.0f;
GLsizei rsize = 50.0f;

GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

GLfloat window_width;
GLfloat window_height;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f,0.0f,0.0f);
    glRectf(x,y,x+rsize,y+rsize);
    glutSwapBuffers();
}

void TimerFunction(int value)
{
	if(x> window_width -rsize || x < -window_width)  // ø‰±‚
		xstep = -xstep;
    
	if(y>window_height -rsize || y < -window_height) // ø‰±‚
		ystep = -ystep;
    
	if(x > window_width-rsize)
		x = window_width-rsize-1;
    
	if(y >window_height-rsize)
		y = window_height-rsize-1;
    
	x +=xstep;
	y +=ystep;
	glutPostRedisplay();
	glutTimerFunc(33,TimerFunction,1);
}

void SetupRC(void)
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glShadeModel(GL_FLAT);
    glFrontFace(GL_CW);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
	{
		window_width = 100.0f; // ø‰±‚
		window_height = 100.0f*h/w; // ø‰±‚
		glOrtho (-100.0f, 100.0f, -window_height, window_height, 1.0, -1.0);
	}
	else
	{
		window_width = 100.0f*w/h; // ø‰±‚
		window_height = 100.0f; // ø‰±‚
		glOrtho (-window_width, window_width, -100.0f, 100.0f, 1.0, -1.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800,600);
	glutCreateWindow("BounceRectangle");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(2000,TimerFunction,1);
    SetupRC();
	glutMainLoop();
	
}
