#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // TITIK
    glPointSize(10);
    glColor3f(1.0, 0.0, 0.0); 
    glBegin(GL_POINTS);
        glVertex2f(-0.5, 0.5);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.5, -0.5);
    glEnd();

    // GARIS
    glLineWidth(3);
    glColor3f(0.0, 0.0, 1.0); 
    glBegin(GL_LINES);
        glVertex2f(-0.8, -0.2);
        glVertex2f(0.8, -0.2);

        glVertex2f(-0.5, -0.7);
        glVertex2f(0.5, -0.3);
    glEnd();

    glFlush();
}

void init() {
    glClearColor(1.0,1.0,1.0,1.0); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1,1,-1,1);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Titik dan Garis");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
}
