#include "iGraphics.h"

void iDraw(void)
{
    iClear();
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
    glutInit(&argc, argv);
    iInitialize(1920,1080,"iGraphics");
    glutFullScreen();
    glutMainLoop();
}
