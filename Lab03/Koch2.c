#include <GL/glut.h>
#include <string.h>
#include <stdio.h>

int InputLevel = 3;
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.5, 0.5, -0.5, 0.5, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void level(char* result, int n) {
    // F -> F+F--F+F
    strcpy(result, "F");
    for (int k = 0; k < n; k++) {
        size_t i = 0;
        while (i < strlen(result)) {
            if (result[i] == 'F') {
                strcpy(result+i+7, result+i);
                memcpy(result+i, "F+F--F+F", 8);
                i+=7;
            }         
            i++;
        }
    }
}

int rotate = 0;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();


    char result[1024];
    level(result, InputLevel);
    glTranslatef(-1, 0, 0);
    float len = 1.0;
    for (int i = 0; i < InputLevel; i++){
        len /= 4.0;
    }

    for (size_t i = 0; i < strlen(result); ++i) {
        if (result[i] == 'F') {
            glBegin(GL_LINES);
                glVertex3f(0, 0, 0);
                glVertex3f(len, 0, 0);
            glEnd();
            glTranslatef(len, 0, 0);

        } else if(result[i] == '+') {
            rotate += 60;
            glRotatef(60, 0, 0, 1); 
        } else if(result[i] == '-') {
            rotate -= 60;
            glRotatef(-60, 0, 0, 1); 
        } 
    }

    glFlush();
    glPopMatrix();
    glutSwapBuffers();
    glutPostRedisplay();
}


int main(int argc, char** argv)
{
    char result[1024];
    for (int i = 0 ; i <=3 ; ++i) {
        level(result, i);
        printf("%d : [%s]\n", i, result);
    }

    glutInit(&argc, argv);
   
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 300);
    glutCreateWindow("cg-lab");
    
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
