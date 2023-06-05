/* Implemeent a DDA Line */

#include <stdio.h>
#include <GL/glut.h>

int x1, y1, x2, y2, arr[2][1000], size = 0, flag = 0, ch = 0;

int ROUND(float a) 
{
    return abs(a + 0.5);
}

void dda(int x1, int y1, int x2, int y2)
 {
    int dx, dy, steps;
    dx = x2 - x1;
    dy = y2 - y1;

    if (abs(dx) > abs(dy)) 
	{
        steps = abs(dx);
    }
	else 
	{
        steps = abs(dy);
    }

    float x, y, xinc, yinc;
    x = x1;
    y = y1;
    xinc = dx / (float) steps;
    yinc = dy / (float) steps;

    arr[0][0] = ROUND(x);
    arr[1][0] = ROUND(y);
    size = 1;

    for (int i = 1; i < steps; i++) 
	{
        x = x + xinc;
        y = y + yinc;
        arr[0][i] = ROUND(x);
        arr[1][i] = ROUND(y);
        size += 1;
    }
}

void drawline() 
{
    glBegin(GL_POINTS);

    switch (ch) 
	{
        case 1:
            for (int i = 0; i < size; i++) 
			{
                glVertex2d(arr[0][i], arr[1][i]);
            }
            break;
        case 2:
            for (int i = 0; i < size; i++)
				{
                if ((i % 2) != 0) 
				{
                    glVertex2d(arr[0][i], arr[1][i]);
                }
            }
            break;
        case 3:
            for (int i = 0; i < size; i++) 
			{
                if ((i % 4) != 0) 
				{
                    glVertex2d(arr[0][i], arr[1][i]);
                }
            }
            break;
        case 4:
            glPointSize(10.0);
            for (int i = 0; i < size; i++) 
			{
                glVertex2d(arr[0][i], arr[1][i]);
            }
            break;
    }

    glEnd();
    glFlush();
}

void mouse(int btn, int state, int mx, int my) 
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
        x1 = mx;
        y1 = 480 - my;
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP) 
	{
        x2 = mx;
        y2 = 480 - my;
        flag = 1;
        
        dda(x1, y1, x2, y2);
    
        glutPostRedisplay();
    }
}

void draw()
 {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2f(320, 0);
    glVertex2f(320, 480);
    glVertex2f(0, 240);
    glVertex2f(640, 240);
    glEnd();

    if (flag == 1 && ch != 0) 
	{
        drawline();
    }

    glFlush();
}

int main(int argc, char** argv) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Practical No 2 -  DDA");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    gluOrtho2D(0, 640, 0, 480);

    glutDisplayFunc(draw);
    glutMouseFunc(mouse);

    printf("\n1.\tSimple Line");
    printf("\n2.\tDotted Line");
    printf("\n3.\tDashed Line");
    printf("\n4.\tSolid Line");
    printf("\n5.\tExit");
    printf("\nEnter Your Choice: ");
    scanf("%d", &ch);

    glutMainLoop();
}