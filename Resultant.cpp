#include "iGraphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI acos(-1)
#define max(a,b) (a>b?a:b)
struct Force
{
	double Magnitude , Angle ; 
}F[10];

double R,Theta;
int n;
double Sqrt(double n)
{
	double l=0.0,r=max(n,1),m=0;
	if(n<0) 
	{
		puts("Root of negative number not possible.");
		return 0;
	}
	while(r-l>.000000001)
	{
		double temp=(l+r)/2;
		if(m==temp) break;
		m=temp;
		if(m*m>n) r=m;
		else l=m;
	}

	return m;
} 




void iDraw(void)
{
    iClear();
    iSetColor(200,200,200);
    iDashedLine(0,iScreenHeight/2,iScreenWidth,iScreenHeight/2);
    iDashedLine(iScreenWidth/2,0,iScreenWidth/2,iScreenHeight);

    int i;
    iSetColor(255,255,255);
    for(i=0;i<n;i++)
    {
    	iLine(iScreenWidth/2,iScreenHeight/2,iScreenWidth/2+5*F[i].Magnitude*cos(Theta),iScreenHeight/2+5*F[i].Magnitude*sin(F[i].Angle));
    }

    iSetColor(255,0,0);
    iStrokeLine(iScreenWidth/2,iScreenHeight/2,iScreenWidth/2+5*R*cos(Theta),iScreenHeight/2+5*R*sin(Theta),2);

    char Radius[10];
    sprintf(Radius,"%lf",R);
    char THETA[10];
    sprintf(THETA,"%lf",Theta*180/PI);
    iText(10,50,Radius);
    iText(10,10,THETA);
}

void iMouse(int button, int state, int mx, int my)
{

}

void iMouseDrag(int mx, int my)
{

}

void iMouseMove(int mx, int my)
{
    
}

void iMouseWheel(int button, int dir, int mx, int my)
{

}

void iKeyboard(unsigned char key)
{
		if(key=='q') exit(0);
}

void iSpecialKeyboard(unsigned char key)
{
    if(key == GLUT_KEY_END) exit(0);
}

void Resultant()
{
	int i;
	double Rx=0,Ry=0;

	for(i=0;i<n;i++)
	{
		Rx+=F[i].Magnitude*cos(F[i].Angle);
		Ry+=F[i].Magnitude*sin(F[i].Angle);
	}

	R = Sqrt(Rx*Rx+Ry*Ry);
	Theta = atan(Ry/Rx) ;
}
int main(int argc,char *argv[])
{
	printf("Number of Forces : ");
	scanf("%d",&n);

	int i;

	for(i=0;i<n;i++)
	{
		scanf("%lf %lf",&F[i].Magnitude,&F[i].Angle);
		F[i].Angle = F[i].Angle * PI / 180 ;
	}

	Resultant();
    glutInit(&argc, argv);
    iInitialize(1920,1080,"iGraphics");
    glutFullScreen();
    glutMainLoop();
}
