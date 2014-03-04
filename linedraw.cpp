/*
Name: Karthik Gopalakrishnan
Roll: 1101CS21

Computer Graphics Lab Assignment 1

ASSUMPTION:
           x1 > x0 and absolute value of slope <= 1
           
           Please only enter input that satisfies both these conditions.


NOTE: When the window opens up, a line in WHITE colour is on the window.
      This line is made using the basic line drawing algorithm.
      
      If you now click on the SPACE BAR, you will see a line in RED colour.
      That line is made using the mid-point line drawing algorithm.
      
      You can click SPACE BAR once again to see the previous line.
      You will notice that both lines are exactly the same.
*/

#define GLUT_STATIC
#include <GL/glut.h>
#include <iostream>
#define round(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
using namespace std;

float x0, y0, x1, y1;
void (*ptr)(void);

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT); /* clear all pixels */
    
    glColor3f(1.0, 1.0, 1.0);    //white color for basic line drawing algorithm
    glBegin(GL_POINTS);
    
    float dx, dy, x, y, slope;
    dx = x1 - x0;
    dy = y1 - y0;
    slope = dy/dx;
    y = y0;
    
    for(x = x0; x <= x1; x++)
    {
          glVertex3f(x, round(y), 0.0);
          y = y + slope;
    }
    
    glEnd();
    
    glFlush(); /* start processing buffered OpenGL routines */
}

void display2(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1.0, 0.0, 0.0);     //red color for mid-point line drawing algorithm    
    glBegin(GL_POINTS);
    
    float x, y, dx, dy, d, delE, delNE;
    x = x0;
    y = y0;
    dx = x1 - x0;
    dy = y1 - y0;
    d = 2*dy - dx;
    delE = 2*dy;
    delNE = 2*(dy - dx);
    glVertex3f(x, y, 0.0);
    
    while(x < x1)
    {
            if(d < 0)
            {
                   d += delE;
                   x += 1;
            }
            else
            {
                d += delNE;
                x += 1;
                y += 1;
            }
            
            glVertex3f(x, y, 0.0);
    }
    glEnd();
    
    glFlush();
}     

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0); /* select clearing color */
    glMatrixMode(GL_PROJECTION); /* initialize viewing values */
    glLoadIdentity();
    glOrtho(-250.0, 250.0, -250.0, 250.0, -1.0, 1.0);
}

void keyboard(unsigned char key, int x, int y)
{
     if(key == 32)     //space
     {
            if(ptr == &display)
            {
                   ptr = &display2;
            }
            else
            {
                ptr = &display;
            }      
            
            ptr();
     }
}

/* Declare initial window size, position, and display mode. Call initialization routines. Register callback function
to display graphics. Enter main loop and process events. */
int main(int argc, char** argv) {
    
    ptr = &display;
    
    cout<<"Enter the two points (x0, y0) and (x1, y1):"<<endl;
    cin>>x0>>y0>>x1>>y1;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    
    glutCreateWindow("Line Drawing");
    init();
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(ptr);
    glutMainLoop();
    
    return 0;
}
