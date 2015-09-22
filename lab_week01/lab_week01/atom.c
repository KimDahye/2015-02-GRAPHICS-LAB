//
//  atom.c
//  lab_week01
//
//  Created by JoJo on 2015. 9. 7..
//  Copyright (c) 2015년 JoJo. All rights reserved.
//

#include <stdio.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <math.h>

#define GL_PI 3.1415f

void SetupRC()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    glEnable(GL_DEPTH_TEST);  //add
    glFrontFace(GL_CCW);      //add
    glEnable(GL_CULL_FACE);   //add
}
void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunc, 1);
}

void ChangeSize(int w, int h)
{
    GLfloat fAspect;
    glViewport(0,0,w,h);
    
    fAspect = (GLfloat)w/(GLfloat)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, fAspect, 1.0f, 500.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTranslatef(0.0f,0.0f, -200.0f);
}

void RenderScene() // add – draw 3 sphere
{
    static GLfloat fElect1=0.0f;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -100.0f);
    glColor3ub(255, 0,0);
    glutSolidSphere(10.0f,15,15);
    
    glPushMatrix();
    glRotatef(fElect1, 0.0f,1.0f,0.0f);
    glTranslatef(90.0f,0.0f,0.0f);
    glColor3ub(255,255,0);
    glutSolidSphere(6.0f,15,15);
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(fElect1, 0.0f,1.0f,0.0f);
    glTranslatef(90.0f,0.0f,0.0f);
    glColor3ub(255,255,0);
    glutSolidSphere(6.0f,15,15);
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(45.0f, 0.0f,0.0f, 1.0f);
    glRotatef(fElect1, 0.0f,1.0f,0.0f);
    glTranslatef(-70.0f, 0.0f,0.0f);
    glutSolidSphere(6.0f,15,15);
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(90.0f,0.0f, 0.0f, 1.0f);
    glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 60.0f);
    glutSolidSphere(6.0f, 15, 15);
    glPopMatrix();
    
    fElect1 += 10.0f;
    if(fElect1 > 360.0f)
        fElect1 = 0.0f;
    
    glutSwapBuffers();
}

void ContorolKey(int key, int x, int y)
{
    
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(512,512);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Atom");
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(33,TimerFunc,1);
    //add
    glutSpecialFunc(ContorolKey);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
}