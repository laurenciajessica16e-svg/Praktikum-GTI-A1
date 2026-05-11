#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

double rotAngle = 0;
double rotAngle1 = 0;

//------------------------------------------------------------
// init
//------------------------------------------------------------
void init()
{
    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60, 1, 1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        0.0, 0.0, 5.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    glEnable(GL_DEPTH_TEST);
}

//------------------------------------------------------------
// display
//------------------------------------------------------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    // rotasi objek
    glRotated(rotAngle, 0, 1, 0);
    glRotated(rotAngle1, 1, 0, 0);

    glColor3f(1.0, 0.0, 0.0);

    glutSolidTeapot(1);

    glPopMatrix();

    glutSwapBuffers();
}

//------------------------------------------------------------
// keyboard
//------------------------------------------------------------
void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        // tombol baru untuk rotasi

        case 'j':
            rotAngle += 10; // putar kiri
            break;

        case 'k':
            rotAngle -= 10; // putar kanan
            break;

        case 'i':
            rotAngle1 += 10; // putar atas
            break;

        case 'm':
            rotAngle1 -= 10; // putar bawah
            break;

        case 'q':
            exit(0);
            break;
    }

    glutPostRedisplay();
}

//------------------------------------------------------------
// main
//------------------------------------------------------------
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(600, 600);

    glutCreateWindow("Rotasi Teapot");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
