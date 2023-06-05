/*
Aim:
Implement Cohen Sutherland line clipping method to clip the polygon with respect the viewport and window. Use mouse click.
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>

#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

int x1, y1, x2, y2; 
int  xmin,ymin,xmax,ymax;
int computeRegionCode(int x, int y) {
    int code = INSIDE;
    if (x < xmin)
        code = LEFT;
    else if (x > xmax)
        code = RIGHT;
    if (y < ymin)
        code = BOTTOM;
    else if (y > ymax)
        code = TOP;
    return code;
}
 
int Round(int a)
{
  return (int)(a+0.5);
}

void ddaline(int x1,int y1,int x2,int y2)
{
  int dx,dy,steps;
  dx=x2-x1;
  dy=y2-y1;
  if( abs(dx)>abs(dy))
  {
    steps=abs(dx);
  }
  else
  {
    steps=abs(dy);
  }
  float xinc,yinc;
  xinc=dx/(float)(steps);
  yinc=dy/(float)(steps);
  float x,y;
  x=(float)x1;
  y=(float)y1;
  glVertex2d(Round(x),Round(y));
  for(int k=0;k<steps;k++)
  {
    x=x+xinc;
    y=y+yinc;
    glVertex2d(Round(x),Round(y));
  }
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	   
     ddaline(xmin,ymin,xmax,ymin);
     ddaline(xmax,ymin,xmax,ymax);
     ddaline(xmax,ymax,xmin,ymax);
     ddaline(xmin,ymax,xmin,ymin);
     glColor3f(1.0,0.0,0.0);
     ddaline(x1,y1,x2,y2);
     glEnd();
    glFlush();

 }
 
 void cohenSutherlandLineClip() 
 {
	int code1 = computeRegionCode(x1, y1);
    int code2 = computeRegionCode(x2, y2);
    int clipped = 0;

    while (1) 
	{
        if ((code1 == 0) && (code2 == 0)) 
		{
            clipped = 1;
            break;
        } 
		else if (code1 & code2) 
		{       
            break;
        }
		else 
		{
            int code_out = code1 ? code1 : code2;
            int x, y;
            if (code_out & TOP) 
			{
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            } 
			else if (code_out & BOTTOM) 
			{
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            } 
			else if (code_out & RIGHT) 
			{
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            } 
			else if (code_out & LEFT) 
			{
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }
			
            if (code_out == code1)
			{
                x1 = x;
                y1 = y;
                code1 = computeRegionCode(x1, y1);
            } 
			else
			{
                x2 = x;
                y2 = y;
                code2 = computeRegionCode(x2, y2);
            }
        }
    }

    if (clipped)
	{
        printf("Line is clipped");
    } 
	else 
	{
        printf("Line completely outside the clipping window\n");
    }
}
 
 void mouse(int btn, int state, int x, int y)
{
  if( btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
     glClear(GL_COLOR_BUFFER_BIT);
     glBegin(GL_POINTS);
     glColor3f(1.0,1.0,0.0);
     ddaline(xmin,ymin,xmax,ymin);
     ddaline(xmax,ymin,xmax,ymax);
     ddaline(xmax,ymax,xmin,ymax);
     ddaline(xmin,ymax,xmin,ymin);
     glColor3f(0.0,1.0,1.0);

     cohenSutherlandLineClip();
     ddaline(x1,y1,x2,y2);
     glEnd();
     glFlush();
 }
}
int main(int argc , char **argv)
{

  printf("Enter the Xmin: \t");
  scanf("%d",&xmin);
    
  printf("Enter the Ymin: \t");
  scanf("%d",&ymin);
    
  printf("Enter the Xmax: \t");
  scanf("%d",&xmax);
    
  printf("Enter the Ymax: \t");
  scanf("%d",&ymax);

  printf("first points: \t");
  scanf("%d\t%d",&x1,&y1);
  printf("Second points: \t");
  scanf("%d\t%d",&x2,&y2);
     
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(640, 480);
  glutCreateWindow("Line Clipping");
  
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glColor3f(1.0,0.0,0.0);
  gluOrtho2D(0, 640, 0, 480);
  
  glutDisplayFunc(draw);
  glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
   
}
