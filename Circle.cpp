#include "iGraphics.h"

int XOX ;
int YOY ;
void iDraw(void)
{
    iClear();
    iSetColor(255,0,0);
    iStrokeCircle(YOY , XOX ,190,10);
    

    iSetColor(255,255,255);
    iStrokeCircle(YOY , XOX ,200,20);
    double t, dt, x1,y1,x2,y2, xp, yp;
    dt = 2*PI/100;
    int r = 200, x = YOY , y = XOX ;
    for(t = 0; t <= 2*PI; t+=dt)
    {
        x1 = x + r * cos(t);
        y1 = y + r * sin(t);
        int R=r+rand()%(250-r+1);

        x2 = x + R * cos(t);
        y2 = y + R * sin(t);
        iStrokeLine(x1, y1 , x2,y2,0);
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

int main(int argc,char *argv[])
{

	srand(time(NULL));
    glutInit(&argc, argv);
    iInitialize(1920,1080,"iGraphics");
    XOX=iScreenHeight/2;
    YOY=iScreenWidth/2;
    glutFullScreen();
    glutMainLoop();
}
