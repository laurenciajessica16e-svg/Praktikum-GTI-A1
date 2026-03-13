#include <GL/glut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    float size = 0.08f;

    // Baris 1 
    glColor3f(1.0f, 0.0f, 0.0f); 
    glBegin(GL_QUADS);
        glVertex2f(-0.04f, 0.35f);
        glVertex2f(0.04f, 0.35f);
        glVertex2f(0.04f, 0.43f);
        glVertex2f(-0.04f, 0.43f);
    glEnd();

    // Baris 2
    glColor3f(1.0f, 1.0f, 0.0f); 
    glBegin(GL_QUADS);
        // kiri
        glVertex2f(-0.12f, 0.27f);
        glVertex2f(-0.04f, 0.27f);
        glVertex2f(-0.04f, 0.35f);
        glVertex2f(-0.12f, 0.35f);
        // kanan
        glVertex2f(0.04f, 0.27f);
        glVertex2f(0.12f, 0.27f);
        glVertex2f(0.12f, 0.35f);
        glVertex2f(0.04f, 0.35f);
    glEnd();

    // Baris 3
    glColor3f(0.0f, 1.0f, 0.0f); 
    glBegin(GL_QUADS);
        // kiri
        glVertex2f(-0.2f, 0.19f);
        glVertex2f(-0.12f, 0.19f);
        glVertex2f(-0.12f, 0.27f);
        glVertex2f(-0.2f, 0.27f);
        // kanan
        glVertex2f(0.12f, 0.19f);
        glVertex2f(0.2f, 0.19f);
        glVertex2f(0.2f, 0.27f);
        glVertex2f(0.12f, 0.27f);
    glEnd();

    // Baris 4
    glColor3f(0.0f, 0.0f, 1.0f); 
    glBegin(GL_QUADS);
        // kiri
        glVertex2f(-0.28f, 0.11f);
        glVertex2f(-0.2f, 0.11f);
        glVertex2f(-0.2f, 0.19f);
        glVertex2f(-0.28f, 0.19f);
        // kanan
        glVertex2f(0.2f, 0.11f);
        glVertex2f(0.28f, 0.11f);
        glVertex2f(0.28f, 0.19f);
        glVertex2f(0.2f, 0.19f);
    glEnd();

    // Baris 5 
    glColor3f(1.0f, 0.0f, 1.0f); 
    glBegin(GL_QUADS);
        // kiri
        glVertex2f(-0.36f, 0.03f);
        glVertex2f(-0.28f, 0.03f);
        glVertex2f(-0.28f, 0.11f);
        glVertex2f(-0.36f, 0.11f);
        // kanan
        glVertex2f(0.28f, 0.03f);
        glVertex2f(0.36f, 0.03f);
        glVertex2f(0.36f, 0.11f);
        glVertex2f(0.28f, 0.11f);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Kubus Bertingkat");

    glClearColor(0.8f, 0.8f, 0.8f, 1.0f); 
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
