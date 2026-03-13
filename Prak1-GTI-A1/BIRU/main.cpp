#include <GL/glut.h>

// Fungsi untuk menampilkan isi window
void Jendela(void)
{
    // Membersihkan layar
    glClear(GL_COLOR_BUFFER_BIT);

    // Memastikan semua perintah OpenGL dijalankan
    glFlush();
}

int main(int argc, char *argv[])
{
    // Inisialisasi GLUT
    glutInit(&argc, argv);

    // Mode tampilan: single buffer + RGBA
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

    // Ukuran window
    glutInitWindowSize(640, 480);

    // Membuat window dengan judul "biru"
    glutCreateWindow("biru");

    // Set warna background (R, G, B, Alpha)
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);  // Biru

    // Daftarkan fungsi display
    glutDisplayFunc(Jendela);

    // Loop utama GLUT
    glutMainLoop();

    return 0;
}

