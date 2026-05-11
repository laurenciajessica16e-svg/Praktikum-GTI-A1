#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ============================================================
   VARIABEL KAMERA
   ============================================================ */
float angle      = 0.0f;
float deltaAngle = 0.0f;
float ratio;
float x  =  0.0f, y = 3.0f, z = 18.0f;   /* posisi kamera */
float lx = -0.0f, ly= 0.0f, lz= -1.0f;   /* arah pandang  */
int   deltaMove  = 0, h, w;

/* ============================================================
   PENCAHAYAAN  (sama persis seperti template)
   ============================================================ */
const GLfloat light_ambient[]  = { 0.3f, 0.3f, 0.3f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 5.0f, 15.0f, 10.0f, 1.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 80.0f };

/* ============================================================
   HELPER: set warna material + gambar face dengan normal otomatis
   ============================================================
   Kita pakai GL_COLOR_MATERIAL sehingga glColor3f cukup untuk
   mengubah warna diffuse/ambient.  Normal dihitung dari 2 edge
   sisi face (cross product) agar lighting bekerja benar.
   ============================================================ */

/* Hitung cross product u x v -> hasil disimpan di out[3] */
static void cross(const float u[3], const float v[3], float out[3])
{
    out[0] = u[1]*v[2] - u[2]*v[1];
    out[1] = u[2]*v[0] - u[0]*v[2];
    out[2] = u[0]*v[1] - u[1]*v[0];
}

/*
 * drawQuad:
 *   Menggambar satu sisi (GL_QUADS) dengan normal yang dihitung otomatis
 *   dari dua edge pertama.  Vertex diberikan CCW saat dilihat dari luar.
 */
static void drawQuad(
    float ax,float ay,float az,
    float bx,float by,float bz,
    float cx,float cy,float cz,
    float dx,float dy,float dz)
{
    float u[3] = { bx-ax, by-ay, bz-az };
    float v[3] = { dx-ax, dy-ay, dz-az };
    float n[3];
    cross(u, v, n);
    glNormal3fv(n);

    glBegin(GL_QUADS);
        glVertex3f(ax,ay,az);
        glVertex3f(bx,by,bz);
        glVertex3f(cx,cy,cz);
        glVertex3f(dx,dy,dz);
    glEnd();
}

/* ============================================================
   PRIMITIF DASAR: KOTAK (box)
   Setiap sisi dipanggil dengan drawQuad -> normal otomatis -> lighting OK
   Posisi tengah (cx,cy,cz), ukuran (w,h,d)
   ============================================================ */
void drawBox(float cx, float cy, float cz,
             float bw, float bh, float bd)
{
    float x0 = cx - bw/2, x1 = cx + bw/2;
    float y0 = cy - bh/2, y1 = cy + bh/2;
    float z0 = cz - bd/2, z1 = cz + bd/2;

    /* depan  (z1) */
    drawQuad(x0,y0,z1,  x1,y0,z1,  x1,y1,z1,  x0,y1,z1);
    /* belakang (z0) */
    drawQuad(x1,y0,z0,  x0,y0,z0,  x0,y1,z0,  x1,y1,z0);
    /* kiri  (x0) */
    drawQuad(x0,y0,z0,  x0,y0,z1,  x0,y1,z1,  x0,y1,z0);
    /* kanan (x1) */
    drawQuad(x1,y0,z1,  x1,y0,z0,  x1,y1,z0,  x1,y1,z1);
    /* atas  (y1) */
    drawQuad(x0,y1,z1,  x1,y1,z1,  x1,y1,z0,  x0,y1,z0);
    /* bawah (y0) */
    drawQuad(x0,y0,z0,  x1,y0,z0,  x1,y0,z1,  x0,y0,z1);
}

/* ============================================================
   RODA: silinder 16-segmen
   cx,cy,cz = titik tengah sumbu silinder
   r = radius, len = panjang (arah Z lokal sebelum transform)
   ============================================================ */
void drawWheel(float cx, float cy, float cz, float r, float len)
{
    int   segs = 16;
    float step = 2.0f * M_PI / segs;

    /* sisi samping silinder */
    glBegin(GL_QUAD_STRIP);
    for(int i = 0; i <= segs; i++) {
        float a  = i * step;
        float nx = cosf(a), ny = sinf(a);
        glNormal3f(nx, ny, 0.0f);
        glVertex3f(cx + r*nx, cy + r*ny, cz - len/2);
        glVertex3f(cx + r*nx, cy + r*ny, cz + len/2);
    }
    glEnd();

    /* tutup depan & belakang (triangle fan) */
    for(int cap = -1; cap <= 1; cap += 2) {
        float zc = cz + cap * len/2;
        glNormal3f(0,0,(float)cap);
        glBegin(GL_TRIANGLE_FAN);
            glVertex3f(cx, cy, zc);
            for(int i = 0; i <= segs; i++) {
                float a = cap * i * step;   /* balik arah CCW untuk cap belakang */
                glVertex3f(cx + r*cosf(a), cy + r*sinf(a), zc);
            }
        glEnd();
    }

    /* hub tengah (kecil) */
    glColor3f(0.75f, 0.75f, 0.80f);
    float hr = r * 0.35f;
    for(int cap = -1; cap <= 1; cap += 2) {
        float zc = cz + cap * len/2;
        glNormal3f(0,0,(float)cap);
        glBegin(GL_TRIANGLE_FAN);
            glVertex3f(cx, cy, zc + cap*0.05f);
            for(int i = 0; i <= segs; i++) {
                float a = cap * i * step;
                glVertex3f(cx + hr*cosf(a), cy + hr*sinf(a), zc);
            }
        glEnd();
    }
}

/* ============================================================
   MOBIL  — dibangun dari rangka kotak + silinder roda
   Seluruh mobil berpusat di (0,0,0) lokal; di display()
   kita pakai glTranslatef agar posisi di atas grid.
   ============================================================ */
void Mobil()
{
    /* ---- BADAN BAWAH (chassis) ---- */
    glColor3f(0.15f, 0.45f, 0.85f);          /* biru mobil */
    drawBox(0.0f, 0.55f, 0.0f,               /* cx,cy,cz   */
            4.4f, 0.85f, 2.0f);              /* w,  h,  d  */

    /* ---- KABIN (atap + dinding kaca) ---- */
    glColor3f(0.12f, 0.38f, 0.75f);
    drawBox(0.0f, 1.45f, 0.05f,
            2.8f, 0.90f, 1.80f);

    /* ---- ATAP ---- */
    glColor3f(0.10f, 0.32f, 0.68f);
    drawBox(0.0f, 1.98f, 0.05f,
            2.6f, 0.14f, 1.70f);

    /* ---- KAP MESIN (hood) ---- */
    glColor3f(0.15f, 0.45f, 0.85f);
    drawBox( 1.50f, 1.05f, 0.0f,
             1.35f, 0.18f, 1.90f);

    /* ---- BAGASI (trunk) ---- */
    drawBox(-1.50f, 1.05f, 0.0f,
             1.35f, 0.18f, 1.90f);

    /* ---- BUMPER DEPAN ---- */
    glColor3f(0.20f, 0.20f, 0.25f);
    drawBox( 2.35f, 0.48f, 0.0f,
             0.22f, 0.42f, 1.70f);

    /* ---- BUMPER BELAKANG ---- */
    drawBox(-2.35f, 0.48f, 0.0f,
             0.22f, 0.42f, 1.70f);

    /* ---- LAMPU DEPAN (kiri & kanan) ---- */
    glColor3f(1.0f, 0.98f, 0.80f);
    drawBox(2.25f, 0.68f,  0.72f,   0.12f, 0.24f, 0.40f);
    drawBox(2.25f, 0.68f, -0.72f,   0.12f, 0.24f, 0.40f);

    /* ---- LAMPU BELAKANG ---- */
    glColor3f(0.90f, 0.12f, 0.10f);
    drawBox(-2.25f, 0.68f,  0.72f,  0.12f, 0.24f, 0.40f);
    drawBox(-2.25f, 0.68f, -0.72f,  0.12f, 0.24f, 0.40f);

    /* ---- GRILL ---- */
    glColor3f(0.10f, 0.10f, 0.12f);
    drawBox(2.26f, 0.52f, 0.0f,     0.12f, 0.30f, 1.10f);

    /* ---- JENDELA SAMPING (warna gelap semi-transparan) ---- */
    glColor3f(0.35f, 0.55f, 0.75f);
    /* kanan */
    drawBox(0.20f, 1.44f,  1.02f,   2.40f, 0.62f, 0.08f);
    /* kiri  */
    drawBox(0.20f, 1.44f, -1.02f,   2.40f, 0.62f, 0.08f);

    /* ---- KACA DEPAN & BELAKANG ---- */
    glColor3f(0.40f, 0.62f, 0.80f);
    drawBox( 1.42f, 1.44f, 0.0f,    0.10f, 0.62f, 1.76f);
    drawBox(-1.42f, 1.44f, 0.0f,    0.10f, 0.62f, 1.76f);

    /* ---- KNALPOT ---- */
    glColor3f(0.55f, 0.55f, 0.60f);
    drawBox(-2.32f, 0.22f, 0.50f,   0.18f, 0.14f, 0.20f);

    /* ============================================================
       RODA — 4 buah
       Posisi Z: ±1.08 (kiri/kanan dari tengah mobil)
       Posisi X:  1.45 (depan), -1.45 (belakang)
       ============================================================ */
    float ry = 0.48f;    /* radius roda */
    float rl = 0.38f;    /* lebar roda  */

    /* roda kanan depan */
    glColor3f(0.12f, 0.12f, 0.15f);
    drawWheel( 1.45f, ry,  1.08f, ry, rl);

    /* roda kiri depan */
    drawWheel( 1.45f, ry, -1.08f, ry, rl);

    /* roda kanan belakang */
    drawWheel(-1.45f, ry,  1.08f, ry, rl);

    /* roda kiri belakang */
    drawWheel(-1.45f, ry, -1.08f, ry, rl);
}

/* ============================================================
   GRID LANTAI
   ============================================================ */
void Grid()
{
    double i;
    const float Z_MIN = -50, Z_MAX = 50;
    const float X_MIN = -50, X_MAX = 50;
    const float gap   = 1.5f;

    /* matikan lighting sementara agar grid tetap abu-abu flat */
    glDisable(GL_LIGHTING);
    glColor3f(0.40f, 0.40f, 0.40f);

    glBegin(GL_LINES);
    for(i = Z_MIN; i < Z_MAX; i += gap) {
        glVertex3f((float)i, 0.0f, Z_MIN);
        glVertex3f((float)i, 0.0f, Z_MAX);
    }
    for(i = X_MIN; i < X_MAX; i += gap) {
        glVertex3f(X_MIN, 0.0f, (float)i);
        glVertex3f(X_MAX, 0.0f, (float)i);
    }
    glEnd();

    glEnable(GL_LIGHTING);
}

/* ============================================================
   KAMERA
   ============================================================ */
void orientMe(float ang)
{
    lx = sinf(ang);
    lz = -cosf(ang);
    glLoadIdentity();
    gluLookAt(x,y,z,  x+lx,y+ly,z+lz,  0,1,0);
}

void moveMeFlat(int i)
{
    x += i * lx * 0.1f;
    z += i * lz * 0.1f;
    glLoadIdentity();
    gluLookAt(x,y,z,  x+lx,y+ly,z+lz,  0,1,0);
}

/* ============================================================
   RESHAPE
   ============================================================ */
void Reshape(int w1, int h1)
{
    if(h1 == 0) h1 = 1;
    w = w1; h = h1;
    ratio = 1.0f * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x,y,z,  x+lx,y+ly,z+lz,  0,1,0);
}

/* ============================================================
   DISPLAY
   ============================================================ */
void display()
{
    if(deltaMove)  moveMeFlat(deltaMove);
    if(deltaAngle) { angle += deltaAngle; orientMe(angle); }

    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* posisikan ulang sumber cahaya agar ikut world space */
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    /* Gambar grid */
    Grid();

    /* Gambar mobil: angkat sedikit agar ban tepat di atas lantai */
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        Mobil();
    glPopMatrix();

    glutSwapBuffers();
    glFlush();
}

/* ============================================================
   KEYBOARD
   ============================================================ */
void pressKey(int key, int xx, int yy)
{
    switch(key) {
        case GLUT_KEY_LEFT  : deltaAngle = -0.01f; break;
        case GLUT_KEY_RIGHT : deltaAngle =  0.01f; break;
        case GLUT_KEY_UP    : deltaMove  =  1;     break;
        case GLUT_KEY_DOWN  : deltaMove  = -1;     break;
    }
}

void releaseKey(int key, int xx, int yy)
{
    switch(key) {
        case GLUT_KEY_LEFT  : if(deltaAngle < 0.0f) deltaAngle = 0.0f; break;
        case GLUT_KEY_RIGHT : if(deltaAngle > 0.0f) deltaAngle = 0.0f; break;
        case GLUT_KEY_UP    : if(deltaMove  > 0)    deltaMove  = 0;    break;
        case GLUT_KEY_DOWN  : if(deltaMove  < 0)    deltaMove  = 0;    break;
    }
}

/* ============================================================
   LIGHTING  (sama dengan template)
   ============================================================ */
void lighting()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

/* ============================================================
   MAIN
   ============================================================ */
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Mobil 3D — Depth & Lighting");

    glutIgnoreKeyRepeat(1);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(Reshape);

    lighting();
    init();

    glutMainLoop();
    return 0;
}
