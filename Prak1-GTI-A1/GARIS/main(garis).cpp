#include <GL/glut.h>

// Fungsi untuk menggambar garis
void Garis(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Atur ketebalan garis
    glLineWidth(2.0f);

    // Mulai menggambar garis
    glBegin(GL_LINES);

        // Warna putih
        glColor3f(1.0f, 1.0f, 1.0f);

        // Titik awal
        glVertex3f(0.0f, 0.20f, 0.0f);

        // Titik akhir
        glVertex3f(0.0f, -0.20f, 0.0f);

    glEnd();

    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Membuat Garis");

    // Background biru
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    glutDisplayFunc(Garis);
    glutMainLoop();

    return 0;
}
