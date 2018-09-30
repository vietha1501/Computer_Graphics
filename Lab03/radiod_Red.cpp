#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <math.h>
using namespace std;
#define radian 3.141592654*2/180.0
#define SIZEBOARD 500 // kich thuoc window


typedef GLfloat twodimpoint[2];
float radius = 1; 
int limit = 180;
void initGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    glClearDepth(1.0f);                   
    glEnable(GL_DEPTH_TEST);   
    glDepthFunc(GL_LEQUAL);    
    glShadeModel(GL_SMOOTH);  
    gluOrtho2D(4, -4, 4, -4);
 
}

void drawCircle(float temp){
    glPushMatrix();
    glBegin(GL_LINE_STRIP);
    for(int i = 0; i <= 180; i++){
        glVertex2f(temp*cos(radian*i), temp*sin(radian*i));
    }
    glEnd();
    glPopMatrix();
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    twodimpoint arrPoint[limit];
    for(int i = 0; i <limit; i++){
        arrPoint[i][0] = radius*cos(i*radian);
        arrPoint[i][1] = radius*sin(i*radian);
        glPushMatrix();
        glRotated(i*2.0, 0.0, 0.0, 1.0);
        glTranslated(0.0, radius, 0.0);
        drawCircle(sqrt(pow(arrPoint[i][0], 2) + pow(arrPoint[i][1] - radius, 2)));
        glPopMatrix();
    }
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
        if(limit > 180)
            limit = 180;
        glutPostRedisplay();
        break;
    }
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(SIZEBOARD, SIZEBOARD);
    glutInitWindowPosition(200, 0);

    glutCreateWindow("radiod-RED");
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    initGL();

    glutMainLoop();

}
