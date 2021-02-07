#include "iGraphics.h"

#define MAX 8
struct
{
	float x,y;
	float Lx,Ly;
	int Sx,Sy;
	int n;
	int Adj[10];
}Node[MAX]=
{
	{0,0,0,0,0,0,5,{1,2,3,4,5}},
	{0,2,0,-12,0,0,3,{0,4,5}},
	{1.5,0,0,0,0,0,3,{0,4,6}},
	{-1.5,0,0,0,0,0,3,{0,5,7}},
	{1.5,1,0,-9,0,0,4,{0,1,2,6}},
	{-1.5,1,0,-6,0,0,4,{0,1,3,7}},
	{3,0,0,-6,1,1,2,{2,4}},
	{-3,0,0,-4,0,1,2,{3,5}}
};



void iDraw(void)
{
    iClear();
    int i,j,n=8;

    for(i=0;i<n;i++)
    {
    	iSetTransparentColor(200,200,200,.5);
    	iFilledCircle(960+200*Node[i].x,400+200*Node[i].y,10);
    }

    for(i=0;i<n;i++)
    {
    	iSetColor(200,200,200);
    	for(j=0;j<Node[i].n;j++)
    	{
    		iLine(960+200*Node[i].x,400+200*Node[i].y,960+200*Node[Node[i].Adj[j]].x,400+200*Node[Node[i].Adj[j]].y);
    	}
    }
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

}

void iSpecialKeyboard(unsigned char key)
{
    if(key == GLUT_KEY_END) exit(0);
}

void Calculate()
{
	int i;
	int FX=0;
	for(i=0;i<MAX;i++)
	{
		FX+=Node[i].Lx;
	}

	for(i=0;i<MAX;i++)
	{
		if(Node[i].Sx)
		{
			Node[i].Lx-=FX;
		}
	}
}
int main(int argc,char *argv[])
{
	Calculate();
    glutInit(&argc, argv);
    iInitialize(1920,1080,"iGraphics");
    glutFullScreen();
    glutMainLoop();
}
