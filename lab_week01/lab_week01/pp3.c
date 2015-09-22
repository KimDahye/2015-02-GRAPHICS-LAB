//
//  pp3.c
//  lab_week01
//
//  Created by JoJo on 2015. 9. 22..
//  Copyright (c) 2015년 JoJo. All rights reserved.
//

#include <stdio.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <math.h>


static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void SetupRC()
{
    glClearColor(1.0f, 1.0f, 1.0f, 6.0f);
    glEnable(GL_DEPTH_TEST);  //add
    glFrontFace(GL_CCW);      //add
    //glEnable(GL_CULL_FACE);   //add
    glShadeModel(GL_SMOOTH);

    
}

void ChangeSize(int w, int h)
{
    GLfloat nRange = 100.0f;
    
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho (-nRange, nRange, -
                 nRange*h/w, nRange*h/w, -nRange*2.0f,
                 nRange*2.0f);               //add
    else
        glOrtho (-nRange*w/h,
                 nRange*w/h, -nRange, nRange, -
                 nRange*2.0f, nRange*2.0f);  //add
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void RenderScene() // add – draw 3 sphere
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    
    glBegin(GL_QUAD_STRIP);
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3d(0.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3d(0.0f, 50.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3d(50.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3d(50.0f, 50.0f, 0.0f);
    
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3d(50.0f, 0.0f, 50.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3d(50.0f, 50.0f, 50.0f);
    
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3d(0.0f, 0.0f, 50.0f);
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3d(0.0f, 50.0f, 50.0f);
    
    glEnd();
    
    glBegin(GL_QUAD_STRIP);
    
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3d(50.0f, 0.0f, 50.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3d(50.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3d(0.0f, 0.0f, 50.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3d(0.0f, 0.0f, 0.0f);
    
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3d(0.0f, 50.0f, 50.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3d(0.0f, 50.0f, 0.0f);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3d(50.0f, 50.0f, 50.0f);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3d(50.0f, 50.0f, 0.0f);

    
    glEnd();
    
    glutSwapBuffers();
}

void ContorolKey(int key, int x, int y)
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

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Color Cube");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(ContorolKey);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
}
