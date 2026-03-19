#include <GL/glut.h>
#include <cmath>

void circle(float cx,float cy,float r){
    glBegin(GL_POLYGON);
    for(int i=0;i<360;i++){
        float t=i*3.1416f/180;
        glVertex2f(cx+cos(t)*r,cy+sin(t)*r);
    }
    glEnd();
}

void road(){
  glPushMatrix();
    glTranslatef(0.0f, -0.2f, 0.0f); // posisi jalan
    glRotatef(-25.0f, 0.0f, 0.0f, 1.0f); // miringin jalan

    // badan jalan
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, -1.0f);
        glVertex2f( 0.1f, -1.0f);
        glVertex2f( 0.1f,  1.0f);
        glVertex2f(-0.1f,  1.0f);
    glEnd();

    // garis tengah jalan
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        for(float y = -1.0f; y < 1.0f; y += 0.2f) {
            glVertex2f(0.0f, y);
            glVertex2f(0.0f, y + 0.1f);
        }
    glEnd();

glPopMatrix();
}

void mountain(){
    glColor3f(0.0f,0.6f,0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-1.0f,0.0f);
        glVertex2f(-0.4f,0.8f);
        glVertex2f(0.2f,0.0f);

        glVertex2f(0.0f,0.0f);
        glVertex2f(0.7f,0.85f);
        glVertex2f(1.2f,0.0f);
    glEnd();
}

void sun(){
    glColor3f(1,1,0);
    circle(0.0f,0.75f,0.12f);
}

void house(){
    glColor3f(1,0.5,0.6);
    glBegin(GL_QUADS);
        glVertex2f(-0.7f,0.1f);
        glVertex2f(-0.2f,0.1f);
        glVertex2f(-0.2f,0.4f);
        glVertex2f(-0.7f,0.4f);
    glEnd();

    glColor3f(1,0.4,0);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.75f,0.4f);
        glVertex2f(-0.15f,0.4f);
        glVertex2f(-0.45f,0.6f);
    glEnd();

    glColor3f(0.5f,0.2f,0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.48f,0.1f);
        glVertex2f(-0.42f,0.1f);
        glVertex2f(-0.42f,0.25f);
        glVertex2f(-0.48f,0.25f);
    glEnd();
}

void car(){
    glPushMatrix();
    glTranslatef(0.28f,-0.38f,0);
    glRotatef(-25,0,0,1);

    glColor3f(0.3,0.8,1);
    glBegin(GL_POLYGON);
        glVertex2f(-0.35f,0.0f);
        glVertex2f(0.35f,0.0f);
        glVertex2f(0.30f,0.18f);
        glVertex2f(-0.25f,0.18f);
    glEnd();

    glColor3f(0.2,0.6,0.9);
    glBegin(GL_POLYGON);
        glVertex2f(-0.20f,0.18f);
        glVertex2f(0.20f,0.18f);
        glVertex2f(0.12f,0.35f);
        glVertex2f(-0.10f,0.35f);
    glEnd();

    glColor3f(0.8,0.9,1);
    glBegin(GL_QUADS);
        glVertex2f(-0.18f,0.20f);
        glVertex2f(-0.02f,0.20f);
        glVertex2f(-0.02f,0.32f);
        glVertex2f(-0.18f,0.32f);

        glVertex2f(0.02f,0.20f);
        glVertex2f(0.18f,0.20f);
        glVertex2f(0.10f,0.32f);
        glVertex2f(0.02f,0.32f);
    glEnd();

    glColor3f(1,1,0);
    glBegin(GL_QUADS);
        glVertex2f(0.35f,0.05f);
        glVertex2f(0.40f,0.07f);
        glVertex2f(0.40f,0.12f);
        glVertex2f(0.35f,0.10f);
    glEnd();

    glColor3f(1,0,0);
    glBegin(GL_QUADS);
        glVertex2f(-0.35f,0.05f);
        glVertex2f(-0.40f,0.07f);
        glVertex2f(-0.40f,0.12f);
        glVertex2f(-0.35f,0.10f);
    glEnd();

    glColor3f(0,0,0);
    circle(-0.22f,-0.05f,0.09f);
    circle(0.22f,-0.05f,0.09f);

    glColor3f(0.7,0.7,0.7);
    circle(-0.22f,-0.05f,0.045f);
    circle(0.22f,-0.05f,0.045f);

    glPopMatrix();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
        glColor3f(0.6,0.9,1);
        glVertex2f(-1,1);
        glVertex2f(1,1);
        glColor3f(0.4,0.8,0.4);
        glVertex2f(1,-1);
        glVertex2f(-1,-1);
    glEnd();

    sun();
    mountain();
    house();
    road();
    car();

    glFlush();
}

void init(){
    glClearColor(1,1,1,1);
    gluOrtho2D(-1,1,-1,1);
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(900,600);
    glutCreateWindow("Pemandangan");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
