#include "iGraphics.h"
#define BlockWidth 110
#define BlockHeight 120
int SelectY=-1,SelectX=-1;
char Word[17][8];

char Player1[20]="Dihan",Player2[20];
void iDraw(void)
{
    iClear();
    int i,j;
    
    iSetColor(255,255,0);
    for(i=0;i<18;i++)
    {
    	iLine(25+i*BlockWidth,10,25+i*BlockWidth,iScreenHeight-110);
    }

    for(i=0;i<9;i++)
    {
    	iLine(25,10+i*BlockHeight,iScreenWidth-25,10+i*BlockHeight);
    }

    if(SelectX>-1)
    {
    	iFilledRectangle(30+SelectX*BlockWidth,15+SelectY*BlockHeight,BlockWidth-10,BlockHeight-10);
    }


    for(i=0;i<17;i++)
    {
    	for(j=0;j<8;j++)
	    {
	    	char temp[2]={Word[i][j],'\0'};
	    	if(SelectX==i&&SelectY==j) iSetColor(0,0,0);
	    	else iSetColor(255,255,0);
	    	iBigText(30+i*BlockWidth,20+j*BlockHeight,temp);
	    }
    }

    iText(50,iScreenHeight-70,Player1);

    
}

void iMouse(int button, int state, int mx, int my)
{
	int i,j;
    for(i=0;i<17;i++)
    {
    	for(j=0;j<8;j++)
	    {
	    	if(mx>=25+i*BlockWidth&&mx<=25+(i+1)*BlockWidth&&my>=10+j*BlockHeight&&my<=10+(j+1)*BlockHeight)
	    	{
	    		SelectY=j;
	    		SelectX=i;
	    		return;
	    	}
	    }
    }
    SelectX=SelectY=-1;
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
	if(key=='\r')
	{
		SelectX=SelectY=-1;
	}

	else if(key=='\b')
	{
		Word[SelectX][SelectY]=0;
	}

	else
	{
		Word[SelectX][SelectY]=((key%'A')%('a'-'A'))+'A';  // To Upper
	}
}

void iSpecialKeyboard(unsigned char key)
{
    if(key == GLUT_KEY_END) exit(0);
}

int main(int argc,char *argv[])
{
	// printf("Player1 : ");
	// scanf("%s",Player1);
	// printf("Player2 : ");
	// scanf("%s",Player2);

    glutInit(&argc, argv);
    iInitialize(1920,1080,"iGraphics");
    glutFullScreen();
    glutMainLoop();
}
