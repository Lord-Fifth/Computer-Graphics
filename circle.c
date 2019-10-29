/* To draw a static clock using Bresenham's circle drawing algorithm */
#include <stdio.h>
#include <GL/glut.h>

// Center of the clock = (300, 340)
int xc = 300, yc = 340;
//centre of pendulum=(300,100)
int xp=300,yp=100;

// Plot eight points using circle's symmetrical property
void plot_pointc(int x, int y)
{
  glBegin(GL_POINTS);
  glVertex2i(xc+x, yc+y);
  glVertex2i(xc+x, yc-y);
  glVertex2i(xc+y, yc+x);
  glVertex2i(xc+y, yc-x);
  glVertex2i(xc-x, yc-y);
  glVertex2i(xc-y, yc-x);
  glVertex2i(xc-x, yc+y);
  glVertex2i(xc-y, yc+x);
  glEnd();
}
void plot_pointp(int x, int y)
{
  glBegin(GL_POINTS);
  glVertex2i(xp+x, yp+y);
  glVertex2i(xp+x, yp-y);
  glVertex2i(xp+y, yp+x);
  glVertex2i(xp+y, yp-x);
  glVertex2i(xp-x, yp-y);
  glVertex2i(xp-y, yp-x);
  glVertex2i(xp-x, yp+y);
  glVertex2i(xp-y, yp+x);
  glEnd();
}
void bresenham_circlec(int r)
{ //bresenham's circle drawing algorithm implementation for clock
  int x=0,y=r;
  float pk=(5.0/4.0)-r;
  plot_pointc(x,y);
  int k;
  while(x < y)
  {
    x = x + 1;
    if(pk < 0)
      pk = pk + 2*x+1;
    else
    {
      y = y - 1;
      pk = pk + 2*(x - y) + 1;
    }
    plot_pointc(x,y);
  }
}
void bresenham_circlep(int r)
{ //bresenham's circle drawing algorithm implementation for pendulum
  int x=0,y=r;
  float pk=(5.0/4.0)-r;
  plot_pointp(x,y);
  int k;
  while(x < y)
  {
    x = x + 1;
    if(pk < 0)
      pk = pk + 2*x+1;
    else
    {
      y = y - 1;
      pk = pk + 2*(x - y) + 1;
    }
    plot_pointp(x,y);
  }
}


// Function to draw a static clock
void static_clock(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  // Draw a clock and pendulum
  bresenham_circlec(100);
  bresenham_circlep(20);
  
  glBegin(GL_LINES);
  // Minute hand
  glVertex2i(xc, yc);
  glVertex2i(xc, yc+95);
  // Hour hand
  glVertex2i(xc, yc);
  glVertex2i(xc+30, yc+50);
  //Pendulum lines from clock
  glVertex2i(304,240);
  glVertex2i(304,120);
  glVertex2i(296,240);
  glVertex2i(296,120);
  glEnd();
  glFlush();
}

void Init()
{
  // Set clear color= black
  glClearColor(0.0,0.0,0.0,0);
  //Set fill= white
  glColor3f(1.0,1.0,1.0);
  gluOrtho2D(0 , 640 , 0 , 480);
}

void main(int argc, char **argv)
{
  // Initialise GLUT library
  glutInit(&argc,argv);
  // Set the initial display mode
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  // Set the initial window position and size
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("bresenham_circle");
  // Initialize drawing colors
  Init();
  glutDisplayFunc(static_clock);
  // Keep displaying until the program is closed
  glutMainLoop();
}
/*
gcc circle.c -lGL -lGLU -lglut
*/
