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

GLfloat x5 = 0.0f;
GLfloat y5 = 0.0f;
GLfloat x2 = 80.0f;
GLfloat y2 = 0.0f;
GLfloat x3 = 50.0f;
GLfloat y3 = -80.0f;
GLfloat x4 = -50.0f;
GLfloat y4 = -80.0f;
GLsizei rsize = 50.0f;

GLfloat x5step = 1.0f;
GLfloat y5step = 1.0f;
GLfloat x2step = 2.0f;
GLfloat y2step = 2.0f;
GLfloat x3step = 1.0f;
GLfloat y3step = 1.0f;
GLfloat x4step = 2.0f;
GLfloat y4step = 2.0f;

GLfloat window_width;
GLfloat window_height;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f,0.0f,0.0f);
    glRectf(x5,y5,x5+rsize,y5+rsize);
    
    glColor3f(0.0f,1.0f,0.0f);
    glRectf(x2,y2,x2+rsize,y2+rsize);
    
    glColor3f(0.0f,0.0f,1.0f);
    glRectf(x3,y3,x3+rsize,y3+rsize);
    
    glColor3f(0.0f,0.0f,0.0f);
    glRectf(x4,y4,x4+rsize,y4+rsize);
    glutSwapBuffers();
}

void updateCoordinate(GLfloat* x, GLfloat* y, GLfloat* xstep, GLfloat* ystep)
{
    if(*x> window_width -rsize || *x < -window_width)  // ø‰±‚
		*xstep = -*xstep;
    
	if(*y>window_height -rsize || *y < -window_height) // ø‰±‚
		*ystep = -*ystep;
    
	if(*x > window_width-rsize)
		*x = window_width-rsize-1;
    
	if(*y >window_height-rsize)
		*y = window_height-rsize-1;
    
    *x += *xstep;
	*y += *ystep;
}

void TimerFunction(int value)
{
    updateCoordinate(&x5,&y5,&x5step,&y5step);
    updateCoordinate(&x2,&y2,&x2step,&y2step);
    updateCoordinate(&x3,&y3,&x3step,&y3step);
    updateCoordinate(&x4,&y4,&x4step,&y4step);
    
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
		window_width = 100.0f;
		window_height = 100.0f*h/w;
		glOrtho (-100.0f, 100.0f, -window_height, window_height, 1.0, -1.0);
	}
	else
	{
		window_width = 100.0f*w/h;
		window_height = 100.0f;
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
	glutCreateWindow("pp1-Bounce Rectangle");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(2000,TimerFunction,1);
    SetupRC();
	glutMainLoop();
	
}

