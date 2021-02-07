/*
 ______   _________ _      _       _
|  ____ \|___   ___| |    | |     | |
| |    \ \   | |   | |____| |     | |
| |    | |   | |   |  ____  |     | |
| |____/ /___| |___| |    | |_____| |
|_______/|_________|_|    |_________|
M A H I R     L A B I B     D I H A N

*/

# include "iGraphics.h"

int Hour,Minute,Second;
int R=255,G=255,B=0;

struct
{
	double Width=1.2;
	int Height=5;
	double Triangle_Height=0.9;
} Font;
/*
	function iDraw() is called again and again by the system.
*/
void VerticalSegment(int X, int Y, int dx, int dy, int size)
	{
		int triangleHeight = Font.Triangle_Height * size;
		double  x[6] = { X , X - dx / 2 , X - dx / 2 , X , X + dx / 2 , X + dx / 2 },
		               y[6] = { Y , Y + triangleHeight , Y + dy + triangleHeight , Y + dy + 2 * triangleHeight , Y + dy + triangleHeight , Y + triangleHeight };

		iFilledPolygon(x, y, 6);
	}
	void HorizontalSegment(int X, int Y, int dx, int dy, int size)
	{
		int triangleHeight = Font.Triangle_Height * size;
		double  x[6] = { X , X + triangleHeight , X + dx + triangleHeight , X + dx + 2 * triangleHeight , X + dx + triangleHeight , X + triangleHeight },
		               y[6] = { Y , Y + dy / 2 , Y + dy / 2 , Y , Y - dy / 2 , Y - dy / 2 };

		iFilledPolygon(x, y, 6);
	}
	void iDrawDigit(int x, int y, int digit, int size)
	{
		if (digit == 0 || digit == 2 || digit == 6 || digit == 8)
			VerticalSegment(x, y, Font.Width * size, Font.Height * size, size);
		if (digit == 0 || digit == 4 || digit == 5 || digit == 6 || digit == 8 || digit == 9)
			VerticalSegment(x, y + Font.Height * size + 2 * Font.Triangle_Height * size, Font.Width * size, Font.Height * size, size);
		if (digit == 0 || digit == 2 || digit == 3 || digit == 5 || digit == 6 || digit == 7 || digit == 8 || digit == 9)
			HorizontalSegment(x, y + 2 * Font.Height * size + 4 * Font.Triangle_Height * size, Font.Height * size, Font.Width * size, size);
		if (digit == 2 || digit == 3 || digit == 4 || digit == 5 || digit == 6 || digit == 8 || digit == 9)
			HorizontalSegment(x, y + Font.Height * size + 2 * Font.Triangle_Height * size, Font.Height * size, Font.Width * size, size);
		if (digit == 0 || digit == 2 || digit == 3 || digit == 5 || digit == 6 || digit == 8 || digit == 9)
			HorizontalSegment(x, y, Font.Height * size, Font.Width * size, size);
		if (digit == 0 || digit == 1 || digit == 3 || digit == 4 || digit == 5 || digit == 6 || digit == 7 || digit == 8 || digit == 9)
			VerticalSegment(x + Font.Height * size + 2 * Font.Triangle_Height * size, y, Font.Width * size, Font.Height * size, size);
		if (digit == 0 || digit == 1 || digit == 2 || digit == 3 || digit == 4 || digit == 7 || digit == 8 || digit == 9)
			VerticalSegment(x + Font.Height * size + 2 * Font.Triangle_Height * size, y + Font.Height * size + 2 * Font.Triangle_Height * size, Font.Width * size, Font.Height * size, size);
	}


void iDraw()
{

    //place your drawing codes here
    iClear();
    iSetColor(R,G,B);
    iDrawDigit(50,350,Hour/10,30);
    iDrawDigit(330,350,Hour%10,30);
    iDrawDigit(710,350,Minute/10,30);
    iDrawDigit(990,350,Minute%10,30);
    iDrawDigit(1370,350,Second/10,30);
    iDrawDigit(1650,350,Second%10,30);

    iFilledCircle(620,400,20);
    iFilledCircle(620,700,20);
    iFilledCircle(1290,400,20);
    iFilledCircle(1290,700,20);
    
}


/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        //printf("x = %d, y= %d\n",mx,my);


    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here

    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(key == 'q')
    {
        exit(0);
    }
    //place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }
    //place your codes for other keys here
}

void Initialize(int width, int height, char* title)
	{
		iScreenHeight = height;
		iScreenWidth = width;
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA) ;
		glutInitWindowSize(width , height ) ;
		glutInitWindowPosition(0, 10) ;
		glutCreateWindow(title) ;
		glClearColor( 0.0 , 0.0 , 0.0 , 0.0 ) ;
		glMatrixMode( GL_PROJECTION) ;
		glLoadIdentity() ;
		glOrtho(0.0 , width , 0.0 , height , -1.0 , 1.0) ;
		glutFullScreen();
		iClear();
		glutDisplayFunc(displayFF) ;
		glutKeyboardFunc(keyboardHandler1FF); //normal
		glutSpecialFunc(keyboardHandler2FF); //special keys
		glutMouseFunc(mouseHandlerFF);
		glutMotionFunc(mouseMoveHandlerFF);
		// glutPassiveMotionFunc(mouseOverHandleFF);
		glutIdleFunc(animFF) ;
		glAlphaFunc(GL_GREATER, 0.0f);
		glEnable(GL_ALPHA_TEST);
		glutSetCursor(GLUT_CURSOR_NONE);
		glutMainLoop();
	}

void Clock()
{
	Second++;
	if(Second==60)
	{
		R=rand()%256;
		G=rand()%256;
		B=rand()%256;
		Minute++;
		if(Minute==60)
		{
			Hour++;
			Minute=0;
		}
		Second=0;
	}
}

void StopWatch()
{
	
}
void iMouseDrag(int mx,int my){}
void iMouseWheel(int a,int b,int c, int d){}
int main(int argc,char *argv[])
{
	time_t Current;
	time(&Current);   
	struct tm *Time = localtime(&Current);
	Hour=Time->tm_hour;
	Minute=Time->tm_min;
	Second=Time->tm_sec+1;
	R=rand()%256;
	G=rand()%256;
	B=rand()%256;
	srand(time(NULL));
    //place your own initialization codes here.
	iSetTimer(1000,Clock);
	iSetTimer(1000,StopWatch);
	glutInit(&argc, argv);
    Initialize(1920,1080, "Demo!");
    return 0;
}
