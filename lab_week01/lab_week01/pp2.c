//
//  atom.c
//  lab_week01
//
//  Created by JoJo on 2015. 9. 7..
//  Copyright (c) 2015년 NHN NEXT. All rights reserved.
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
    static GLfloat fElect1=0.0f;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -100.0f);
    glColor3ub(255, 255,0);
    glutSolidSphere(10.0f,15,15);
    
    glRotatef(fElect1, 0.0f,1.0f,0.0f);
    glTranslatef(90.0f,0.0f,0.0f);
    glColor3ub(0,0,255);
    glutSolidSphere(10.0f,15,15);
    glPushMatrix();
    
    glPopMatrix();
    glRotatef(fElect1, 0.0f,1.0f,0.0f);
    glTranslatef(-20.0f,0.0f,0.0f);
    glColor3ub(50,50,50);
    glutSolidSphere(6.0f,15,15);

    
    fElect1 += 5.0f;
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
    glutInitWindowSize(800,512);
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