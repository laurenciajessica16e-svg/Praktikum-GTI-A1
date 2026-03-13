#include <GL/glut.h>

// Fungsi untuk menggambar titik
void point(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0,0.5,0.0);
        glVertex2f(0.2,0.4);
        glVertex2f(0.1,0.3);
        glVertex2f(0.3,0.3);
        glVertex2f(0.35,0.45);
        glVertex2f(0.2,0.55);
        glVertex2f(0.05,0.45);
    glEnd();

    // TRIANGLE STRIP
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.7,0.0,1.0);
        glVertex2f(0.5,0.5);
        glVertex2f(0.6,0.3);
        glVertex2f(0.7,0.5);
        glVertex2f(0.8,0.3);
    glEnd();

    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Titik");

    // Warna background biru
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    glutDisplayFunc(point);
    glutMainLoop();

    return 0;
}
