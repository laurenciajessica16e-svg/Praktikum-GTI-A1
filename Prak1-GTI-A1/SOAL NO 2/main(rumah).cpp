#include <GL/glut.h>

void gambar(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Badan rumah
    glBegin(GL_QUADS);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex2f(0.4f,0.2f);
        glVertex2f(-0.4f,0.2f);
        glVertex2f(-0.4f,-0.2f);
        glVertex2f(0.4f,-0.2f);
    glEnd();

    // Atap rumah
    glBegin(GL_TRIANGLE_STRIP);
    	glColor3f(0.8f,0.0f,0.0f);
    	glVertex2f(-0.5f, 0.2f);  
    	glVertex2f(0.0f, 0.5f);   
    	glVertex2f(0.5f, 0.2f);   
    	glVertex2f(0.0f, 0.5f);   
	glEnd();

    // Pintu
    glBegin(GL_QUAD_STRIP);
        glColor3f(0.5f,0.2f,0.0f);
        glVertex2f(-0.1f,-0.2f);
        glVertex2f(-0.1f,0.05f);
        glVertex2f(0.1f,-0.2f);
        glVertex2f(0.1f,0.05f);
    glEnd();

    // Jendela kiri
    glBegin(GL_LINE_LOOP);
        glColor3f(0.0f,0.5f,0.0f);
        glVertex2f(-0.3f,0.05f);
        glVertex2f(-0.15f,0.05f);
        glVertex2f(-0.15f,0.15f);
        glVertex2f(-0.3f,0.15f);
    glEnd();
    
    //Hiasan Jendela Kiri
    glBegin(GL_TRIANGLE_FAN);
    	glColor3f(0.0f, 0.5f, 0.0f);
    	glVertex2f(-0.225f, 0.1f); 
    	glVertex2f(-0.225f, 0.05f); 
    	glVertex2f(-0.15f, 0.1f);  
    	glVertex2f(-0.225f, 0.15f); 
    	glVertex2f(-0.3f, 0.1f);   
    	glVertex2f(-0.225f, 0.05f); 
	glEnd();
	
	//Hiasan Jendela Kanan
	glBegin(GL_TRIANGLE_FAN);
    	glColor3f(0.0f, 0.5f, 0.0f);
    	glVertex2f(0.225f, 0.1f);   
    	glVertex2f(0.225f, 0.05f);  
    	glVertex2f(0.3f, 0.1f);     
    	glVertex2f(0.225f, 0.15f);  
    	glVertex2f(0.15f, 0.1f);    
    	glVertex2f(0.225f, 0.05f); 
	glEnd();
	
    // Jendela kanan
    glBegin(GL_LINE_LOOP);
        glColor3f(0.0f,0.5f,0.0f);
        glVertex2f(0.15f,0.05f);
        glVertex2f(0.3f,0.05f);
        glVertex2f(0.3f,0.15f);
        glVertex2f(0.15f,0.15f);
    glEnd();

    // Garis detail
    glBegin(GL_LINE_STRIP);
        glColor3f(0.0f,0.5f,0.0f);
        glVertex2f(-0.1f,-0.05f);
        glVertex2f(0.1f,-0.05f);
    glEnd();

    // Titik dekorasi
    glPointSize(5);
    glBegin(GL_POINTS);
        glColor3f(1.0f,1.0f,0.0f);
        glVertex2f(0.0f,0.35f);
    glEnd();

    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Gambar Rumah");

    glClearColor(1.0f,1.0f,0.0f,1.0f);

    glutDisplayFunc(gambar);

    glutMainLoop();
    return 0;
}
