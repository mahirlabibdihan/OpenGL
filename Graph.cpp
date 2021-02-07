

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include "iGraphics.h"
#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include<stack>
#include<time.h>
using namespace std;
#define HEIGHT 1080
#define WIDTH 1920
#define min(a,b)  (a<b?(a):(b))
#define max(a,b)  (a>b?(a):(b))


int x = 300, y = 300,r=2;
float Zoom=100.0,LastZoom=100.0;
double Dir;
int MouseX,MouseY,LastMouseX,LastMouseY;
int Draw=0,Erase=0,Grid=1,Fill=0,EraserSize=10,FillX=-1,FillY=-1,Undo=0,LineX=-1,LineY=-1;
int I,J;
int R,G,B,Size=1,Line=0;
int ZoomX=WIDTH/2,ZoomY=HEIGHT/2;

double Angle=0,Time=0;


/*
	function iDraw() is called again and again by the system.
*/

typedef struct
{
    unsigned char R,G,B,Show=0;
}Color;

Color Graph[WIDTH+1][HEIGHT+1];
stack<pair<int,int>> History;

static int slices = 16;
static int stacks = 16;

void reshapeFF(int width, int height)
{
   // const float ar = (float) width / (float) height;
   glViewport(0, 0, width, height);
   // glMatrixMode(GL_PROJECTION);
   // glLoadIdentity();
   // glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity() ;
}


double iSiny(double Amplitude , double WaveLength , double time=0,int x=0,double PhaseAngle = 0,double dir=0, int yAxis = iScreenWidth/2)
{

    double A=Amplitude , Y = Max(3,WaveLength) , O = PI*PhaseAngle/180,t=time , d=PI*dir/180;
    return A*sin((2*PI*t/Y)-cos(d)*(2*PI*(x-yAxis)/Y));
}

double iSinx(double Amplitude , double WaveLength , double time=0,int y=0,double PhaseAngle = 0,double dir=0, int xAxis = iScreenHeight/2)
{
    double A=Amplitude , Y = Max(3,WaveLength) , O = PI*PhaseAngle/180,t=time , d=PI*dir/180;
    return A*sin((2*PI*t/Y)-sin(d)*(2*PI*(y-xAxis)/Y)+O);
}

void iSin(double Amplitude , double WaveLength , double time=0,double dir=0,double PhaseAngle = 0,int xAxis = iScreenHeight/2 , int yAxis = iScreenWidth/2 , int x1 = 0 , int x2 = iScreenWidth )
{
    int i;
    double A=Amplitude , Y = Max(3,WaveLength) , O = PhaseAngle,t=time;
    glBegin(GL_LINE_STRIP);
    for(i=x1;i<=x2;i++)
    {
        double x=i;
        double y=xAxis+iSiny(A,Y,t,i,O,dir);
        glVertex2f(i,y);
    }
    glEnd();
}


double iSinRy(double Amplitude , double WaveLength , double time=0, int x=0,double PhaseAngle = 0, int yAxis = iScreenWidth/2)
{
    double A=Amplitude , Y = Max(3,WaveLength) , O = PI*PhaseAngle/180,t=time;
    return A*sin((2*PI*t/Y)-cos(PI)*(2*PI*(x-yAxis)/Y)+O);
}

double iSinVRx(double Amplitude , double WaveLength , double time=0,int y=0,double PhaseAngle = 0, int xAxis = iScreenHeight/2)
{
    double A=Amplitude , Y = Max(3,WaveLength) , O = PI*PhaseAngle/180,t=time;
    return A*sin((2*PI*t/Y)-sin(-PI/2)*(2*PI*(y-xAxis)/Y)+O);
}


double iSinVx(double Amplitude , double WaveLength , double time=0,int y=0,double PhaseAngle = 0, int xAxis = iScreenHeight/2)
{
    double A=Amplitude , Y = Max(3,WaveLength) , O = PI*PhaseAngle/180,t=time;

    return A*sin((2*PI*t/Y)-sin(PI/2)*(2*PI*(y-xAxis)/Y)+O);
}



void iFilledSin(double Amplitude , double WaveLength , double time=0,double dir=0,double PhaseAngle = 0,int xAxis = iScreenHeight/2 , int yAxis = iScreenWidth/2 , int x1 = 0 , int x2 = iScreenWidth )
{
    int i,j;
    double A=Amplitude , Y = Max(3,WaveLength) , O = PhaseAngle,t=time;
    for(j=x1;j<=x2;j=i)
    {
        glBegin(GL_POLYGON);
        for(i=j;i<=j+Y/2;i++)
        {
            if((int)(iSiny(A,Y,t,i,O,dir))==0)
            {
                glVertex2f(i,xAxis+iSiny(A,Y,t,i,O,dir));
                break;
            }
            glVertex2f(i,xAxis+iSiny(A,Y,t,i,O,dir));
        }
        glVertex2f(j,xAxis);
        glEnd();
        if(i==j) i++;
    }
}


void iSinR(double Amplitude , double WaveLength , double time=0,double PhaseAngle = 0,int xAxis = iScreenHeight/2 , int yAxis = iScreenWidth/2 , int x1 = 0 , int x2 = iScreenWidth )
{
    int i;
    double A=Amplitude , Y = Max(3,WaveLength) , O = PI*PhaseAngle/180,t=time;
    glBegin(GL_LINE_STRIP);
    for(i=x1;i<=x2;i++)
    {
        glVertex2f(i,xAxis+iSinRy(A,Y,t,i,O));
    }
    glEnd();
}



void iFilledSinR(double Amplitude , double WaveLength , double time=0,double PhaseAngle = 0,int xAxis = iScreenHeight/2 , int yAxis = iScreenWidth/2 , int x1 = 0 , int x2 = iScreenWidth )
{
    int i,j;
    double A=Amplitude , Y = Max(3,WaveLength) , O = PI*PhaseAngle/180,t=time;
    for(j=x1;j<=x2;j=i)
    {
        glBegin(GL_POLYGON);
        for(i=j;i<=j+Y/2;i++)
        {
            if((int)(iSinRy(A,Y,t,i,O))==0)
            {
                glVertex2f(i,xAxis+iSinRy(A,Y,t,i,O));
                break;
            }
            glVertex2f(i,xAxis+iSinRy(A,Y,t,i,O));
        }
        glVertex2f(j,xAxis);
        glEnd();
        if(i==j) i++;
    }
}

void iSinV(double Amplitude , double WaveLength , double time=0,double PhaseAngle = 0,int xAxis = iScreenHeight/2 , int yAxis = iScreenWidth/2 , int y1 = 0 , int y2 = iScreenHeight)
{
    int i;
    double A=Amplitude , Y = Max(3,WaveLength) , O = PI*PhaseAngle/180,t=time;
    glBegin(GL_LINE_STRIP);
    for(i=y1;i<=y2;i++)
    {
        glVertex2f(yAxis+iSinVx(A,Y,t,i,O),i);
    }
    glEnd();
}


void iFilledSinV(double Amplitude , double WaveLength , double time=0,double PhaseAngle = 0,int xAxis = iScreenHeight/2 , int yAxis = iScreenWidth/2 , int y1 = 0 , int y2 = iScreenHeight )
{
    int i,j;
    double A=Amplitude , Y = Max(3,WaveLength) , O = PI*PhaseAngle/180,t=time;
    for(j=y1;j<=y2;j=i)
    {
        glBegin(GL_POLYGON);
        for(i=j;i<=j+Y/2;i++)
        {
            if((int)(iSinVx(A,Y,t,i,O))==0)
            {
                glVertex2f(yAxis+iSinVx(A,Y,t,i,O),i);
                break;
            }
            glVertex2f(yAxis+iSinVx(A,Y,t,i,O),i);
        }
        glVertex2f(yAxis,j);
        glEnd();
        if(i==j) i++;
    }
}


void iSinVR(double Amplitude , double WaveLength , double time=0,double PhaseAngle = 0,int xAxis = iScreenHeight/2 , int yAxis = iScreenWidth/2 , int y1 = 0 , int y2 = iScreenHeight)
{
    int i;
    double A=Amplitude , Y = Max(3,WaveLength) , O = PI*PhaseAngle/180,t=time;
    glBegin(GL_LINE_STRIP);
    for(i=y1;i<=y2;i++)
    {
        glVertex2f(yAxis+iSinVRx(A,Y,t,i,O),i);
    }
    glEnd();
}


void iFilledSinVR(double Amplitude , double WaveLength , double time=0,double PhaseAngle = 0,int xAxis = iScreenHeight/2 , int yAxis = iScreenWidth/2 , int y1 = 0 , int y2 = iScreenHeight )
{
    int i,j;
    double A=Amplitude , Y = Max(3,WaveLength) , O = PI*PhaseAngle/180,t=time;
    for(j=y1;j<=y2;j=i)
    {
        glBegin(GL_POLYGON);
        for(i=j;i<=j+Y/2;i++)
        {
            if((int)(iSinVRx(A,Y,t,i,O))==0)
            {
                glVertex2f(yAxis+iSinVRx(A,Y,t,i,O),i);
                break;
            }
            glVertex2f(yAxis+iSinVRx(A,Y,t,i,O),i);
        }
        glVertex2f(yAxis,j);
        glEnd();
        if(i==j) i++;
    }
}




void iDashedLine(double x1,double y1,double x2,double y2)
{
    int i;
    if(x1==x2)
    {
        double m=(x1-x2)/(y1-y2);
        double c=m*(iScreenHeight/2-y1)+x1;
        for(i=y1;i<=y2;i+=30)
        {
            glBegin(GL_LINE_STRIP);
            glVertex2f(x1,i);
            glVertex2f(x1,i+15);
            glEnd();
        }
    }
    else
    {
        double m=(y1-y2)/(x1-x2);
        double c=m*(iScreenWidth/2-x1)+y1;
        for(i=x1;i<=x2;i+=30)
        {
            glBegin(GL_LINE_STRIP);
            glVertex2f(i,m*i+c);
            glVertex2f(i+15,m*(i+15)+c);
            glEnd();
        }
    }
    
    
}
void DCurve()
{
    int i,j;
    double A=2*Zoom,Y=8*Zoom , t=Time;

    iSetColor(255,255,0);
    iSin(2*Zoom,Zoom*8,Time);
    iSetTransparentColor(255,255,0,.25);    
    iFilledSin(2*Zoom,Zoom*8,Time);

    iSetColor(0,255,0);
    iSin(-2*Zoom,Zoom*8,Time,180);
    iSetTransparentColor(0,255,0,.25);    
    iFilledSin(-2*Zoom,Zoom*8,Time,180);

    iSetColor(255,0,0);
    iSinV(-2*Zoom,8*Zoom,Time);
    iSetTransparentColor(255,0,0,.25);
    iFilledSinV(-2*Zoom,8*Zoom,Time);

    iSetColor(191,0,255);
    iSinVR(2*Zoom,8*Zoom,Time);
    iSetTransparentColor(191,0,255,.25);
    iFilledSinVR(2*Zoom,8*Zoom,Time);

    
    // glBegin(GL_LINE_STRIP);
    // for(i=0;i<=iScreenWidth;i++)
    // {
    //     double x=i;
    //     double y=A*sin(0.01*x);
    //     glVertex2f(x,((x-960)*sin(PI/4)-y*cos(PI/4))+540);
    // }
    // glEnd();

    // glBegin(GL_LINE_STRIP);
    // for(i=0,j=0;i<=iScreenWidth;i++)
    // {
    //     double x=i;
    //     double y=j;
    //     glVertex2f(x,540+((x-960)*(sin(0)+cos(0))/(-sin(0)+cos(0))));
    // }
    // glEnd();


    // iSetColor(191,0,255);
    // glBegin(GL_LINE_STRIP);
    // for(i=0;i<=iScreenWidth;i++)
    // {
    //     int y=iScreenHeight/2+iSiny(2*Zoom,Zoom*8,Time,i)+iSiny(2*Zoom,8*Zoom,Time,i,90);
    //     glVertex2f(i,y);
    // }
    // glEnd();


    // iSetTransparentColor(191,0,255,.25);
    // for(j=0;j<=iScreenWidth;j=i)
    // {
    //     glBegin(GL_POLYGON);
    //     for(i=j;i<=j+Y/2;i++)
    //     {
    //         int y=iScreenHeight/2+iSiny(2*Zoom,Zoom*8,Time,i)+iSiny(2*Zoom,8*Zoom,Time,i,90);
    //         if((int)(iSiny(2*Zoom,Zoom*8,Time,i)+iSiny(2*Zoom,8*Zoom,Time,i,90))==0)
    //         {
    //             break;
    //         }
    //         glVertex2f(i,y);
    //     }
    //     glVertex2f(j,iScreenHeight/2);
    //     glEnd();
    //     if(i==j) i++;
    // }
    Time+=1;
}

void DLine(double Angle , double yIntersect=0 ,  int yAxis = iScreenWidth/2 , int xAxis = iScreenHeight/2)
{
    if(fmod(Angle,90)==0)
    {
        if(fmod(Angle,180)==0)
        {
            double c=yIntersect;
            double y1 = xAxis + c , y2 = xAxis + c;
            double x1 = 0 , x2 = iScreenWidth;
            iLine(x1,y1,x2,y2);
        }
        else
        {
            double c=yIntersect;
            double y1 = 0 , y2 = iScreenHeight;
            double x1 = xAxis , x2 = xAxis;
            iLine(x1,y1,x2,y2);
        }
    }
    else
    {
        double m=tan(PI*Angle/180),c=yIntersect;
        double y1 = 0 , y2 = iScreenHeight;
        double x1 = ((y1-xAxis-c)/m) + yAxis , x2 = ((y2-xAxis-c)/m) + yAxis;
        iLine(x1,y1,x2,y2);
    }

}
void iDraw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
//

//    iBigText(200, 225, "This is antialiased.");
//    iText(200, 225, "This is antialiased.");
        //place your drawing codes here
//    iClear();
//
    int j,i;




    if(Grid)
    {
        iSetTransparentColor(100,100,100,0.5);
        for(i=960;i<1920;i+=Zoom/2)
        {
            iLine(i,0,i,1080);
            iLine(960-(i-960),0,960-(i-960),1080);
        }
        for(i=540;i<1080;i+=Zoom/2)
        {
            iLine(0,i,1950,i);
            iLine(0,540-(i-540),1950,540-(i-540));
        }
        iSetTransparentColor(255,255,255,0.5);
//        iLine(0,540,1920,540);
//        iLine(960,0,960,1080);
        iDashedLine(0,MouseY,iScreenWidth,MouseY);
        iDashedLine(MouseX,0,MouseX,iScreenHeight);
    }



    iRotate(iScreenWidth/2,iScreenHeight/2,20);
    DCurve();

    iSetColor(R,G,B);

    for(i=0;i<WIDTH;i++)
    {
        for(j=0;j<HEIGHT;j++)
        {
            if(Graph[i][j].Show)
            {
                iSetColor(Graph[i][j].R,Graph[i][j].G,Graph[i][j].B);
                iPoint(i,j,Size);
            }

        }
    }

     iSetTransparentColor(50,50,50,.7);
     iFilledRectangle(1580,0,340,70);
     iFilledCircle(1860,1020,30);

     iSetColor(150,150,150);
     iStrokeLine(1845,1005,1875,1035,2);
     iStrokeLine(1875,1005,1845,1035,2);
    for(i=1590;i<=1845;i++)
    {
        for(j=50;j<60;j++)
        {
            iSetColor(i-1590,0,0);
            iPoint(i,j);
        }
        for(j=30;j<40;j++)
        {
            iSetColor(0,i-1590,0);
            iPoint(i,j);
        }
        for(j=10;j<20;j++)
        {
            iSetColor(0,0,i-1590);
            iPoint(i,j);
        }
    }



    iSetTransparentColor(255,255,255,.3);
    iFilledCircle(1590+R,55,10);
    iFilledCircle(1590+G,35,10);
    iFilledCircle(1590+B,15,10);
    iSetColor(R,G,B);
    for(i=1860;i<=1910;i+=5)
    {
        for(j=10;j<=60;j+=5)
        {
            iPoint(i,j,Size);
        }
    }

     if(Fill)
    {
        iSetColor(R,G,B);
        for(i=MouseX-15;i<=MouseX+15;i+=5)
        {
            for(j=MouseY-15;j<=MouseY+15;j+=5)
            {
                iPoint(i,j,Size);
            }
        }
    }

    if(Erase)
    {
        iSetTransparentColor(255,255,255,.3);
        iFilledRectangle(MouseX-EraserSize,MouseY-EraserSize,2*EraserSize,2*EraserSize);
    }

    else
    {
        iSetTransparentColor(255,255,255,.3);
        iFilledCircle(MouseX,MouseY,10);
        iSetColor(R,G,B);
        iPoint(MouseX,MouseY,Size+1);

    }
    

    char Direction[10];
    sprintf(Direction,"%.2lf",Dir);
    iText(10,1050,Direction);

}



void FillColor(int x,int y)
{
    if(x>=0&&x<WIDTH&&y>=0&&y<HEIGHT&&x!=WIDTH/2&&y!=HEIGHT/2)
    {
        if(!Graph[x][y].Show)
        {
            Graph[x][y]={R,G,B,1};
            History.push({x,y});
            int i,j;
            for(i=y+1;i<y+4;i++)
            {
                if(Graph[x][i].Show) break;
                if(x==WIDTH/2||i==HEIGHT/2||x==WIDTH||i==HEIGHT||x==0||i==0)
                {
//                    Graph[x][i]={R,G,B,1};
//                    History.push({x,i});
                    break;
                }
            }
            if(i==y+4)   FillColor(x,y+4);

            for(i=y-1;i>y-4;i--)
            {
                if(Graph[x][i].Show) break;
                if(x==WIDTH/2||i==HEIGHT/2||x==WIDTH||i==HEIGHT||x==0||i==0)
                {
//                    Graph[x][i]={R,G,B,1};
//                    History.push({x,i});
                    break;
                }
            }
            if(i==y-4)  FillColor(x,y-4);

            for(i=x+1;i<x+4;i++)
            {
                if(Graph[i][y].Show) break;
                if(i==WIDTH/2||y==HEIGHT/2||i==WIDTH||y==HEIGHT||i==0||y==0)
                {
//                    Graph[i][y]={R,G,B,1};
//                    History.push({i,y});
                    break;
                }
            }
            if(i==x+4) FillColor(x+4,y);

            for(i=x-1;i>x-4;i--)
            {
                if(Graph[i][y].Show) break;
                if(i==WIDTH/2||y==HEIGHT/2||i==WIDTH||y==HEIGHT||i==0||y==0)
                {
//                    Graph[i][y]={R,G,B,1};
//                    History.push({i,y});
                    break;
                }
            }
            if(i==x-4) FillColor(x-4,y);
        }
    }
}

void iMouse(int button, int state, int mx, int my)
{
    Draw=0;
    MouseX=mx;
    MouseY=my;
    Erase=0;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        //printf("x = %d, y= %d\n",mx,my);

        if(mx>=1590&&mx<=1845&&my>=5&&my<=25)
        {
            B=mx-1590;
        }
        else if(mx>=1590&&mx<=1845&&my>=25&&my<=45)
        {
            G=mx-1590;
        }

        else if(mx>=1590&&mx<=1845&&my>=45&&my<=65)
        {
            R=mx-1590;
        }
        else if(mx>=1860&&mx<=1910&&my>=10&&my<=60)
        {
            Fill=1;
        }
        else if(mx>=1830&&mx<=1870&&my>=1010&&my<=1050)
        {
            exit(0);
        }

        else if(Fill)
        {
            History.push({-1,-1});
            FillColor(mx,my);
            Fill=!Fill;
            FillX=mx;
            FillY=my;


        }
        else if(Line)
        {
            if(LineX==-1)
            {
                LineX=mx;
                LineY=my;
                Graph[mx][my]={R,G,B,1};
                History.push({-1,-1});
                History.push({LineX,LineY});

            }

            else
            {
                int i;

                History.push({-1,-1});
                for(i=min(mx,LineX);i<=max(mx,LineX);i++)
                {
                    int j=(1.0*(LineY-my)*(i-LineX)/(LineX-mx))+LineY;
                    if(!Graph[i][j].Show)
                    {
                        Graph[i][j]={R,G,B,1};
                        History.push({i,j});
                    }
                }

                for(i=min(my,LineY);i<=max(my,LineY);i++)
                {
                    int j=(1.0*(LineX-mx)*(i-LineY)/(LineY-my))+LineX;
                    if(!Graph[j][i].Show)
                    {
                        Graph[j][i]={R,G,B,1};
                        History.push({j,i});
                    }
                }
                LineX=mx;
                LineY=my;
            }
        }
        else
        {
            Draw=1;
            if(Graph[mx][my].Show!=!Erase)
            {
                Graph[mx][my].Show=!Erase;

                if(Graph[mx][my].Show)
                {
                     History.push({-1,-1});
                    Graph[mx][my]={R,G,B,1};

                    History.push({mx,my});
                }
            }

        }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        Erase=1;
    }

        // if(button==4)
        // {
        //     Zoom-=10;
        // }
}
void iMouseDrag(int mx, int my)
{
    if(Fill&&!Erase) return;


    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here

    int i,j,k;

    int dx=mx-MouseX,dy=my-MouseY;
    Dir=(atan(abs(1.0*dy/dx))*180)/acos(-1);

    if(Dir<=45)
    {
            for(i=min(MouseX,mx);i<=max(mx,MouseX);i++)
            {
                int y=(1.0*(my-MouseY)*(i-mx)/(mx-MouseX))+my;
                if(Draw)
                {
                     if(Graph[i][y].Show!=!Erase)
                     {
                        Graph[i][y].Show=!Erase;

                    if(Graph[i][y].Show)
                     {
                        Graph[i][y]={R,G,B,1};
                        History.push({i,y});
                     }
                     }

                }


                if(Erase)
                {
                    for(j=i-EraserSize;j<=i+EraserSize;j++)
                    {
                        for(k=y-EraserSize;k<=y+EraserSize;k++)
                        {
                            if(j>=0&&j<WIDTH&&k>=0&&k<HEIGHT)
                                {
                                    Graph[j][k].Show=!Erase;

                                }
                        }
                    }
                }
            }
    }


    else
    {

            for(i=min(MouseY,my);i<=max(my,MouseY);i++)
            {
                int x=(1.0*(mx-MouseX)*(i-my)/(my-MouseY))+mx;
                if(Draw)
                {
                    if(Graph[x][i].Show!=!Erase)
                    {
                     Graph[x][i].Show=!Erase;

                     if(Graph[x][i].Show)
                    {
                        Graph[x][i]={R,G,B,1};
                        History.push({x,i});

                    }
                    }

                }

                if(Erase)
                {
                    for(j=i-EraserSize;j<=i+EraserSize;j++)
                    {
                         for(k=x-EraserSize;k<=x+EraserSize;k++)
                        {
                             if(j>=0&&j<WIDTH&&k>=0&&k<HEIGHT)
                                {
                                    Graph[k][j].Show=!Erase;

                                }

                        }

                    }
                }
            }
    }
    MouseX=mx;
    MouseY=my;
}
void iMouseMove(int mx, int my)
{
     MouseX=mx;
     MouseY=my;
}

void iMouseWheel(int button, int dir, int mx, int my)
{
    ZoomX=mx;
    ZoomY=iScreenHeight-my;
    if (dir > 0)
    {
        Zoom+=10;
    }
    else
    {
        if(Zoom>10)
        Zoom-=10;
    }

    return;
}

void iKeyboard(unsigned char key)
{
 if(key == 'q')
    {
        exit(0);
    }
    if(key=='z')
    {
        // memset(Graph,0,sizeof(Graph));
        Undo=!Undo;
    }
    if(key=='e')
    {
        Erase=!Erase;
    }
    if(key=='g')
    {
        Grid=!Grid;
    }
    if(key=='f')
    {
        Fill=!Fill;
    }
    if(key=='u')
    {
        while(1)
        {
            if(History.empty()) break;
            pair<int,int> temp=History.top();
            if(temp.first==-1)
            {
                while(History.top().first==-1)
                {
                    History.pop();
                    if(History.empty()) break;
                }
                History.pop();
                break;
            }
            History.pop();
            Graph[temp.first][temp.second].Show=0;
        }
    }
    if(key=='l')
    {
        Line=!Line;
        if(!Line) LineX=LineY=-1;
    }
    glutPostRedisplay();
}


void iSpecialKeyboard(unsigned char key)
{
    if(key == GLUT_KEY_END)
    {
        exit(0);
    }
    if(key == GLUT_KEY_DOWN)
    {
        if(Zoom>10)
        Zoom-=10;
    }
    if(key == GLUT_KEY_UP)
    {
        Zoom+=10;
    }
}



int main(int argc,char *argv[])
{
    srand(time(NULL));
    R=rand()%256;
    G=rand()%256;
    B=rand()%256;
    glutInit(&argc, argv);
    iInitialize(1920,1080,"Graph");
    glutFullScreen();
    glutMainLoop();
}
