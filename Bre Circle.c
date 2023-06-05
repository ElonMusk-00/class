/*
3 Done
Aim:
Implement Bresenham's circle drawing algorithm to draw any object. The object should be displayed in all the quadrants with respect to center and radius. 
Take the center point using Mouse Interfacing/click.

*/

#include <GL/glut.h>
#include <math.h>

void plot_circle(int xc, int yc, int r) {
    int x = 0;
	int y = r;
    int d = 3 - 2 * r;
    glVertex2d(xc + x, yc + y);
    while (x <= y) 
	{
        glVertex2d(xc + x, yc + y);
        glVertex2d(xc - x, yc + y);
        glVertex2d(xc + x, yc - y);
        glVertex2d(xc - x, yc - y);
        glVertex2d(xc + y, yc + x);
        glVertex2d(xc - y, yc + x);
        glVertex2d(xc + y, yc - x);
        glVertex2d(xc - y, yc - x);
        
        if (d < 0) 
		{
            d += 4 * x + 6;
        } 
		else 
		{
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void display() 
{
    glBegin(GL_LINES);
    glVertex2f(-320,0);
    glVertex2f(320,0);
    glVertex2f(0,-240);
    glVertex2f(0,240);
    glEnd();
    glFlush();
                                   
    glBegin(GL_POINTS);             // Plot the circle in all quadrants with respect to center and radius
    plot_circle(0, 0, 190);
    glEnd();
	
    glutSwapBuffers();              // Swap the front and back buffers
}

int main(int argc, char** argv)
 {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640 , 480);
    glutCreateWindow("Bresenham Circle Drawing Algorithm");
	
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    gluOrtho2D(-320, 320,-240,240);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}