/*
5 done 
Aim: Implement following 2D transformations on the object with respect to axis.
*/

#include<stdio.h>
#include<GL/glut.h>
#include<math.h>

int v,tx,ty,sx,sy,xf,yf;
int input[3][10];
int output[3][10];
float trans[3][3];
float scale[3][3];
float rotate[3][3];
float xr,yr;
double angle,radian,cosv,sinv;
const float pi=3.14159;

void multiplication(float trans[3][3],int input[3][10],int output[3][10])
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<v;j++)
		{
			output[i][j]=0;
			for(int k=0;k<3;k++)
			{
				output[i][j]+=trans[i][k]*input[k][j];
			}
		}
	}
}

int Round(float a)
{
  return (int)(a+0.5);
}
 
void ddaline(int x1,int y1,int x2,int y2)
 {
     int dx,dy,steps;
      dx=x2-x1;
      dy=y2-y1;
     
      if(abs(dx)>abs(dy))
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
     
     x=x1;
     y=y1;
     
     int k;
     
     glVertex2d(Round(x),Round(y));
     
     for(k=0;k<steps;k++)
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
	
	int i;
	for(i=0;i<v-1;i++)
	{
		ddaline(input[0][i],input[1][i],input[0][i+1],input[1][i+1]);	
	}
	ddaline(input[0][i],input[1][i],input[0][0],input[1][0]);
	
	glColor3f(0.0,0.0,1.0);
	int a;
	for(a=0;a<v-1;a++)
	{
		ddaline(output[0][a],output[1][a],output[0][a+1],output[1][a+1]);	
	}
	
	ddaline(output[0][a],output[1][a],output[0][0],output[1][0]);
	glEnd();
	glFlush();
}

int main(int argc,char**argv)
{
	int choice;
	printf("enter the no of vertices:");
	scanf("%d",&v);
	
	int i;
	for(i=0;i<v;i++)
	{
		printf("enter the x value:");
		scanf("%d",&input[0][i]);
		printf("enter the y value:");
		scanf("%d",&input[1][i]);
		input[2][i]=1;
	}
	printf("enter which operation you want to perform:\n 1:translation 2:scaling 3:rotation\n");
	scanf("%d",&choice);
	
	switch(choice)
	{
	case 1:
		printf("enter the valueof tx:");
		scanf("%d",&tx);
		printf("enter the valueof ty:");
		scanf("%d",&ty);
		
		for(int l=0;l<3;l++)
		{
			for(int m=0;m<3;m++)
			{
				if(l==m)
				{
					trans[l][m]=1;
				}
				else
				{
					trans[l][m]=0;
				}
			}
			
		}
		trans[0][2]=tx;
		trans[1][2]=ty;
		
		multiplication(trans,input,output);
		break;
		
		case 2:
			printf("enter the value of sx:");
			scanf("%d",&sx);
			printf("enter the value of sy:");
			scanf("%d",&sy);
			
			printf("enter the fixed point:");
			printf("enter the value of xf:");
			scanf("%d",&xf);
			printf("enter the value of yf:");
			scanf("%d",&yf);
			
			for(int l=0;l<3;l++)
			{
				for(int m=0;m<3;m++)
				{
					scale[l][m]=0;
				}
			}
			scale[0][0]=sx;
			scale[1][1]=sy;
			scale[0][2]=xf*(1-sx);
			scale[1][2]=yf*(1-sy);
			scale[2][2]=1;
			
			multiplication(scale,input,output);
			break;
			
		case 3:
			printf("enter the value of xr:");
			scanf("%f",&xr);
			printf("enter the value of yr:");
			scanf("%f",&yr);
			
			printf("enter the value of angle :");
			scanf("%lf",&angle);
			
			radian=angle*(pi/180);
			cosv=cos(radian);
			sinv=sin(radian);
		
			rotate[0][0]=cosv;
			rotate[0][1]=-sinv;
			rotate[0][2]=(xr*(1-cosv))+(yr*sinv);
			rotate[1][0]=sinv;
			rotate[1][1]=cosv;
			rotate[1][2]=(yr*(1-cosv))-(xr*sinv);
			rotate[2][0]=0;
			rotate[2][1]=0;
			rotate[2][2]=1;
			
			multiplication(rotate,input,output);
			break;
	}
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutCreateWindow("Translation");
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);
	gluOrtho2D(0,640,0,480);
	glutDisplayFunc(draw);
	glutMainLoop();
	
	return 0;
}