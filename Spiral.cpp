#include "iGraphics.h"

int Count;
void iDraw(void)
{
	iClear();
	glBegin(GL_LINE_STRIP);
    for(double Rad=0;Rad<Count*PI/2;Rad+=PI/100)
    {
    	double R=10*Rad;
    	iSetColor(R+50,R*cos(Rad)+50,R*sin(Rad)+50);
    	glVertex2f(960+R*cos(Rad),540+R*sin(Rad));//1+R/100
    }
    glEnd();
}

void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(Count<70) Count++;
	} 
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if(Count>0)	Count--;
	}
}

void iSpecialKeyboard(unsigned char key)
{
    if(key == GLUT_KEY_END) exit(0);
}

int main(int argc,char *argv[])
{
    glutInit(&argc, argv);
    iInitialize(1920,1080,"iGraphics");
    glutFullScreen();
    glutMainLoop();
}

void iMouseDrag(int mx, int my){}
void iMouseMove(int mx, int my){}
void iMouseWheel(int button, int dir, int mx, int my){}
void iKeyboard(unsigned char key){}