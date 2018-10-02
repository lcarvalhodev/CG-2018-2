#include <cmath>
#include <iostream>

#include <GL/glut.h>
#include <GL/glext.h>

#define PI 3.14

float W = 100.0, H = 100.0;

bool inter = true;
float x = 10, y = 10;

void colorePonto(){
   
    glClear (GL_COLOR_BUFFER_BIT);    
    glLoadIdentity();   
    glBegin(GL_POINTS); 
    if(inter)        
    	glColor3f(0, 0, 1);
    else
    	glColor3f(0, 0, 0);
    glVertex3f(x, y, -1.);       
    glEnd();    
    glFlush();
}


void init(void){
    glClearColor((195%255)/255., (150%255)/255., (160%255)/255., 0.0);
}

// exemplo do professor pra pintar de acordo com o tamanho da tela
void resize(int w, int h)
{
    int wsize = w, hsize = h;
    if (h >= w)
    {
        hsize = w*H/W;
        glViewport(0, (h-hsize)/2, wsize, hsize);
    }
    else if (h < w)
    {
        wsize = h*W/H;
        glViewport((w-wsize)/2, 0,  wsize, hsize);
    }
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-W/2, W/2, -H/2, H/2, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(200, 200);
    glutInitWindowPosition(000, 000);
    glutCreateWindow("Snow Man");
    glutDisplayFunc(colorePonto);
    glutReshapeFunc(resize);
   
    init();
    glutMainLoop();
}

