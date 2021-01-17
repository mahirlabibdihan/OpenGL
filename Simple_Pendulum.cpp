#include "iGraphics.h"

double X=960,Y=700,L=300,BallX=X,BallY=Y-L,BallR=30,A,E,KE,PE;
int Hold=0,Pause=0;
int DirY=0,DirX=0;
double Dir=0;
double Theta=0,ThetaMax=0;


void iMouse(int button, int state, int mx, int my)
{
	if(button== GLUT_LEFT_BUTTON &&  state == GLUT_DOWN)
	{
		if(mx>=BallX-BallR&&mx<=BallX+BallR&&my>=BallY-BallR,my<=BallY+BallR)
		{
			Hold=1;
			Dir=0;
		}		
	}

	if(button== GLUT_LEFT_BUTTON &&  state == GLUT_UP)
	{
			Hold=0;
	}
}

void iDraw(void)
{
    iClear();

    iSetColor(200,200,200);
   	

   	
   	iLine(X,Y,BallX,BallY);
   	
	iSetTransparentColor(100,100,100,.5);
   	iDashedLine(X-L,Y-L,X+L,Y-L);
   	iDashedLine(X-L,Y,X+L,Y);
   	iDashedLine(X-L,Y-L,X-L,Y);
   	iDashedLine(X+L,Y-L,X+L,Y);
   	iDashedLine(X,Y-L,X,Y);

   	double i,j;


   	for(i=PI;i+PI/72<=2*PI;i+=PI/36)
   	{
   		int x1 = X + L * cos(i);
   		int y1 = Y + L * sin(i);

   		int x2 = X + L * cos(i+PI/72);
   		int y2 = Y + L * sin(i+PI/72);

   		iLine(x1,y1,x2,y2);
   	}

   	// for(j=1;j*BallR<L;j++)
   	// {
   	// 	for(i=-PI/2+Theta;i+PI/72<=0;i+=PI/36)
	   // 	{
	   // 		int x1 = X + j * BallR * cos(i);
	   // 		int y1 = Y + j * BallR * sin(i);

	   // 		int x2 = X + j * BallR * cos(i+PI/72);
	   // 		int y2 = Y + j * BallR * sin(i+PI/72);

	   // 		iLine(x1,y1,x2,y2);
	   // 	}
   	// }
   	

   	iSetTransparentColor(100,100,100,.2);
   	glBegin(GL_POLYGON);
   	for(i=0;i>=-PI/2+Theta;i-=PI/72)
   	{
   		int x = X + L * cos(i);
   		int y = Y + L * sin(i);
   		glVertex2f(x,y);

   	}
   	glVertex2f(BallX,BallY);
   	glVertex2f(X,Y);
   	glEnd();

   	iSetTransparentColor(200,200,200,.5);
   	iFilledCircle(BallX,BallY,BallR);




   	
}
void iMouseDrag(int mx, int my)
{
	if(Hold)
	{
		if(my>Y) my=Y;
		Theta=atan((mx-X)/(Y-my));
		BallY=Y-L*cos(Theta);
		BallX=X+L*sin(Theta);
		ThetaMax=Theta;
		if(Theta>0)
		Dir=-.01;
		else if(Theta<0)
		Dir=.01;
	}
}

void iMouseMove(int mx, int my)
{
    
}

void iMouseWheel(int button, int dir, int mx, int my)
{

}

void iKeyboard(unsigned char key)
{
	if(key==' ') Pause=!Pause;
}	

void iSpecialKeyboard(unsigned char key)
{
    if(key == GLUT_KEY_END) exit(0);
}

void Oscilliation()
{
	if(Hold||Pause) return;
	Theta+=Dir;

	BallY=Y-L*cos(Theta);
	BallX=X+L*sin(Theta);

	if((int)fabs(180*Theta/PI)==(int)(180*ThetaMax/PI)) 
	{
		if(Theta>0 && Dir>0)
		Dir=-Dir;
		else if(Theta<0 && Dir<0)
		Dir=-Dir;
	}
}
int main(int argc,char *argv[])
{
	BallX=960,BallY=540;
	iSetTimer(10,Oscilliation);
    glutInit(&argc, argv);
    iInitialize(1920,1080,"iGraphics");
    glutFullScreen();
    glutMainLoop();
}
