/*
 * main.cpp
 * Kubus 3D dengan Tekstur Gambar di SETIAP SISI (6 sisi, 6 gambar berbeda)
 * Menggunakan OpenGL + GLUT
 *
 * File gambar yang dibutuhkan (letakkan di folder project):
 *   face1.bmp  face2.bmp  face3.bmp
 *   face4.bmp  face5.bmp  face6.bmp
 *
 * Kontrol:
 *   Panah Kiri/Kanan  : Rotasi sumbu Y
 *   Panah Atas/Bawah  : Rotasi sumbu X
 *   ESC               : Keluar
 */

#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include "imageloader.h"
using namespace std;

// -----------------------------------------
//  VARIABEL GLOBAL
// -----------------------------------------
GLuint textures[6];          // 6 texture ID untuk 6 sisi kubus
float  rotX = 25.0f;         // Sudut rotasi sumbu X
float  rotY = -35.0f;        // Sudut rotasi sumbu Y

// Nama file gambar untuk tiap sisi
const char* textureFiles[6] = {
    "face1.bmp",   // Depan  (Front)
    "face2.bmp",   // Belakang (Back)
    "face3.bmp",   // Kiri   (Left)
    "face4.bmp",   // Kanan  (Right)
    "face5.bmp",   // Atas   (Top)
    "face6.bmp"    // Bawah  (Bottom)
};

// -----------------------------------------
//  LOAD SATU TEXTURE DARI FILE BMP
// -----------------------------------------
void loadTexture(int index, const char* filename) {
    Image* img = loadBMP(filename);
    if (!img) {
        // Jika file tidak ditemukan, buat tekstur warna solid sebagai fallback
        cout << "Menggunakan warna fallback untuk: " << filename << endl;

        // Warna fallback berbeda tiap sisi
        unsigned char colors[6][3] = {
            {255, 100, 100},  // Merah muda  - Depan
            {100, 255, 100},  // Hijau       - Belakang
            {100, 100, 255},  // Biru        - Kiri
            {255, 255, 100},  // Kuning      - Kanan
            {255, 100, 255},  // Magenta     - Atas
            {100, 255, 255}   // Cyan        - Bawah
        };

        // Buat tekstur 2x2 piksel warna solid
        unsigned char fallback[4 * 3];
        for (int i = 0; i < 4; i++) {
            fallback[i*3]   = colors[index][0];
            fallback[i*3+1] = colors[index][1];
            fallback[i*3+2] = colors[index][2];
        }

        glBindTexture(GL_TEXTURE_2D, textures[index]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0,
                     GL_RGB, GL_UNSIGNED_BYTE, fallback);
        return;
    }

    // Bind dan upload tekstur ke GPU
    glBindTexture(GL_TEXTURE_2D, textures[index]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // gluBuild2DMipmaps otomatis membuat mipmap
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB,
                      img->width, img->height,
                      GL_RGB, GL_UNSIGNED_BYTE, img->pixels);

    delete img;
    cout << "Berhasil memuat: " << filename << endl;
}

// -----------------------------------------
//  INISIALISASI
// -----------------------------------------
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Background hitam
    glEnable(GL_DEPTH_TEST);                 // Aktifkan depth test
    glEnable(GL_TEXTURE_2D);                 // Aktifkan texturing

    // Generate 6 texture ID sekaligus
    glGenTextures(6, textures);

    // Load semua tekstur
    for (int i = 0; i < 6; i++) {
        loadTexture(i, textureFiles[i]);
    }

    // Setup pencahayaan sederhana
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightPos[]    = {2.0f, 3.0f, 4.0f, 1.0f};
    GLfloat lightAmbient[]= {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat lightDiffuse[]= {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);

    // Agar tekstur tidak dipengaruhi pencahayaan secara berlebihan
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

// -----------------------------------------
//  GAMBAR SATU SISI KUBUS BERTEKSTUR
// -----------------------------------------
void drawFace(int texIndex,
              float x1, float y1, float z1,  // Titik sudut 1
              float x2, float y2, float z2,  // Titik sudut 2
              float x3, float y3, float z3,  // Titik sudut 3
              float x4, float y4, float z4,  // Titik sudut 4
              float nx, float ny, float nz)  // Normal vector
{
    glBindTexture(GL_TEXTURE_2D, textures[texIndex]);

    glBegin(GL_QUADS);
        glNormal3f(nx, ny, nz);

        // Koordinat tekstur (UV) + posisi vertex
        // UV (0,0) = sudut kiri bawah, (1,1) = sudut kanan atas
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y1, z1);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x2, y2, z2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x3, y3, z3);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x4, y4, z4);
    glEnd();
}

// -----------------------------------------
//  GAMBAR KUBUS LENGKAP (6 SISI)
// -----------------------------------------
void drawCube() {
    float s = 1.0f;  // setengah ukuran kubus

    //        texIdx  ---- 4 vertex ------------------------------------  normal
    // Depan  (Front)  : z = +s
    drawFace(0,  -s,-s,+s,  +s,-s,+s,  +s,+s,+s,  -s,+s,+s,   0, 0, 1);
    // Belakang (Back) : z = -s
    drawFace(1,  +s,-s,-s,  -s,-s,-s,  -s,+s,-s,  +s,+s,-s,   0, 0,-1);
    // Kiri   (Left)   : x = -s
    drawFace(2,  -s,-s,-s,  -s,-s,+s,  -s,+s,+s,  -s,+s,-s,  -1, 0, 0);
    // Kanan  (Right)  : x = +s
    drawFace(3,  +s,-s,+s,  +s,-s,-s,  +s,+s,-s,  +s,+s,+s,   1, 0, 0);
    // Atas   (Top)    : y = +s
    drawFace(4,  -s,+s,+s,  +s,+s,+s,  +s,+s,-s,  -s,+s,-s,   0, 1, 0);
    // Bawah  (Bottom) : y = -s
    drawFace(5,  -s,-s,-s,  +s,-s,-s,  +s,-s,+s,  -s,-s,+s,   0,-1, 0);
}

// -----------------------------------------
//  CALLBACK DISPLAY
// -----------------------------------------
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Posisi kamera
    gluLookAt(0.0, 0.0, 4.0,   // Eye
              0.0, 0.0, 0.0,   // Center
              0.0, 1.0, 0.0);  // Up

    // Terapkan rotasi
    glRotatef(rotX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);

    // Set material putih agar tekstur tampil dengan warna asli
    GLfloat matDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat matSpecular[]= {0.3f, 0.3f, 0.3f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT,  GL_SHININESS, 30.0f);

    drawCube();

    glutSwapBuffers();
}

// -----------------------------------------
//  CALLBACK RESHAPE
// -----------------------------------------
void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / (float)h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// -----------------------------------------
//  CALLBACK KEYBOARD (Panah untuk rotasi)
// -----------------------------------------
void specialKeys(int key, int /*x*/, int /*y*/) {
    switch (key) {
        case GLUT_KEY_LEFT:  rotY -= 5.0f; break;
        case GLUT_KEY_RIGHT: rotY += 5.0f; break;
        case GLUT_KEY_UP:    rotX -= 5.0f; break;
        case GLUT_KEY_DOWN:  rotX += 5.0f; break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int /*x*/, int /*y*/) {
    if (key == 27) exit(0);  // ESC untuk keluar
}

// -----------------------------------------
//  AUTO ROTATE (opsional)
// -----------------------------------------
void timer(int /*value*/) {
    rotY += 0.5f;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);  // ~60fps
}

// -----------------------------------------
//  MAIN
// -----------------------------------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Kubus Tekstur - Setiap Sisi Berisi Gambar");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, timer, 0);  // Aktifkan auto-rotate

    cout << "=== Kubus Tekstur 6 Sisi ===" << endl;
    cout << "Letakkan file: face1.bmp s/d face6.bmp di folder ini" << endl;
    cout << "Kontrol: Panah = Rotasi manual | ESC = Keluar" << endl;

    glutMainLoop();
    return 0;
}
