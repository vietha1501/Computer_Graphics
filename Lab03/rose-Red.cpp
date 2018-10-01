#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;
#define radian 3.141592654*2/180.0
#define SIZEBOARD 400 // kich thuoc window


typedef GLfloat twodimpoint[2];
float radius = 1; 
int limit = 4;
void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
    glClearDepth(1.0f);                   
    glEnable(GL_DEPTH_TEST);   
    glDepthFunc(GL_LEQUAL);    
    glShadeModel(GL_SMOOTH);   
    gluOrtho2D(-2, 2, -2, 2);
    
    
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_LINE_STRIP);
    for(int i = 0; i <=180; i++){
        glPushMatrix();
        float temp = radius*sin(limit*i*radian);
        twodimpoint point = {temp*cos(i*radian), temp*sin(i*radian)};
        glVertex2fv(point);
        glPopMatrix();
    }
    glEnd();
    glutSwapBuffers();
}




void keyboard(int key, int x, int y){
    switch(key){
    case GLUT_KEY_DOWN:
        limit--;
        if(limit < 0)
            limit = 0;
        glutPostRedisplay();
        break;
    case GLUT_KEY_UP:
        limit++;
        if(limit > 10)
            limit = 10;
        glutPostRedisplay();
        break;
    }
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(SIZEBOARD, SIZEBOARD);
    glutInitWindowPosition(300, 0);

    glutCreateWindow("rose-red");
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    initGL();

    glutMainLoop();

}
