

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
#include<vector>
#include<time.h>
using namespace std;
#define HEIGHT 1080
#define WIDTH 1920
#define min(a,b)  (a<b?(a):(b))
#define max(a,b)  (a>b?(a):(b))

struct Color {
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

int x = 300, y = 300;
float Zoom=100.0,LastZoom=100.0;
double Dir;
int MouseX,MouseY,LastMouseX,LastMouseY;
int Draw=0,Grid=1,Fill=0,EraserSize=10,FillX=-1,FillY=-1,Undo=0,LineX=-1,LineY=-1;
int I,J;
int R,G,B,Size=1;
int ZoomX=WIDTH/2,ZoomY=HEIGHT/2;
int r=15;



/*
	function iDraw() is called again and again by the system.
*/


Color Graph[WIDTH+1][HEIGHT+1];
vector<pair<int,int>> History;

int Index=-1;
int Line=-1;




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
    iClear();
    



int i;
    iSetTransparentColor(100,100,100,.3);
    glBegin(GL_POLYGON);
    for(i = 0; i < History.size(); i++){
        glVertex2f(History[i].first,History[i].second);
    }
    glEnd();


    
    
    for(i = 0; i < History.size()-1; i++)
    {
        if(Line==i) iSetColor(255,255,255);
        else iSetColor(155,155,155);
        iDashedLine(History[i].first,History[i].second,History[i+1].first,History[i+1].second);
    }
    if(Line==i) iSetColor(255,255,255);
    else iSetColor(155,155,155);
    iDashedLine(History[0].first,History[0].second,History[i].first,History[i].second);
    
    for(i = 0; i < History.size(); i++)
    {
        if(Index==i) iSetTransparentColor(255,255,255,.5);
        else iSetTransparentColor(100,100,100,.5);
        iFilledCircle(History[i].first,History[i].second,15);
    }

}





void iMouse(int button, int state, int mx, int my)
{
    int i,j;
    Index=-1;

    for(i=0;i<History.size();i++)
    {
        if(mx>=History[i].first-r&&mx<=History[i].first+r&&my>=History[i].second-r&&my<=History[i].second+r)
        {
            Index=i;
            return;
        }
    }
    Index=-1;



    for(i=0;i<History.size()-1;i++)
    {
        int x1=History[i].first;
        int y1=History[i].second;
        int x2=History[i+1].first;
        int y2=History[i+1].second;
        
        double dir = (atan(abs(1.0*(y1-y2)/(x1-x2)))*180)/acos(-1);
        

        if(dir>45)
        {
            double m=1.0*(x1-x2)/(y1-y2);
            double c=x1-y1*m;
            for(j=min(y1,y2);j<=max(y1,y2);j++)
            {
                if(mx>=m*j+c-5&&mx<=m*j+c+5&&my==j)
                {
                    History.insert(History.begin()+i+1,{m*j+c,my});
                    return;
                }
            }
        }
        else
        {
            double m=1.0*(y1-y2)/(x1-x2);
            double c=y1-x1*m;
            for(j=min(x1,x2);j<=max(x1,x2);j++)
            {
                if(mx==j&&my>=m*j+c-5&&my<=m*j+c+5)
                {
                    History.insert(History.begin()+i+1,{mx,m*j+c});
                    return;
                }
            }
        }
    }


        int x1=History[i].first;
        int y1=History[i].second;
        int x2=History[0].first;
        int y2=History[0].second;
        

        double dir = (atan(abs(1.0*(y1-y2)/(x1-x2)))*180)/acos(-1);
        
        

        if(dir>45)
        {
            double m=1.0*(x1-x2)/(y1-y2);
            double c=x1-y1*m;
            for(j=min(y1,y2);j<=max(y1,y2);j++)
            {
                if(mx>=m*j+c-5&&mx<=m*j+c+5&&my==j)
                {
                    History.insert(History.begin()+i+1,{m*j+c,my});
                    return;
                }
            }
        }
        else
        {
            double m=1.0*(y1-y2)/(x1-x2);
            double c=y1-x1*m;
            for(j=min(x1,x2);j<=max(x1,x2);j++)
            {
                if(mx==j&&my>=m*j+c-5&&my<=m*j+c+5)
                {
                    History.insert(History.begin()+i+1,{mx,m*j+c});
                    return;
                }
            }
        }


}

void Erase(vector<pair<int,int>>&V,pair<int,int> P)
{
    int i;
    for(i=0;i<V.size();i++)
    {
        if(V[i]==P)  V.erase(V.begin()+i);
    }
}
void iMouseDrag(int mx, int my)
{
    if(Index==-1) return;
    int i;
    History.erase(History.begin()+Index);
    History.insert(History.begin()+Index,{mx,my});
}
void iMouseMove(int mx, int my)
{
    int i,j;
    Index=-1;
    Line=-1;
    for(i=0;i<History.size();i++)
    {
        if(mx>=History[i].first-r&&mx<=History[i].first+r&&my>=History[i].second-r&&my<=History[i].second+r)
        {
            Index=i;
            return;
        }
    }
    

    for(i=0;i<History.size()-1;i++)
    {
        int x1=History[i].first;
        int y1=History[i].second;
        int x2=History[i+1].first;
        int y2=History[i+1].second;
        
        double dir = (atan(abs(1.0*(y1-y2)/(x1-x2)))*180)/acos(-1);
        

        if(dir>45)
        {
            double m=1.0*(x1-x2)/(y1-y2);
            double c=x1-y1*m;
            for(j=min(y1,y2);j<=max(y1,y2);j++)
            {
                if(mx>=m*j+c-5&&mx<=m*j+c+5&&my==j)
                {
                    Line=i;
                    return;
                }
            }
        }
        else
        {
            double m=1.0*(y1-y2)/(x1-x2);
            double c=y1-x1*m;
            for(j=min(x1,x2);j<=max(x1,x2);j++)
            {
                if(mx==j&&my>=m*j+c-5&&my<=m*j+c+5)
                {
                    Line=i;
                    return;
                }
            }
        }
    }


        int x1=History[i].first;
        int y1=History[i].second;
        int x2=History[0].first;
        int y2=History[0].second;
        

        double dir = (atan(abs(1.0*(y1-y2)/(x1-x2)))*180)/acos(-1);
        
        

        if(dir>45)
        {
            double m=1.0*(x1-x2)/(y1-y2);
            double c=x1-y1*m;
            for(j=min(y1,y2);j<=max(y1,y2);j++)
            {
                if(mx>=m*j+c-5&&mx<=m*j+c+5&&my==j)
                {
                    Line=i;
                    return;
                }
            }
        }
        else
        {
            double m=1.0*(y1-y2)/(x1-x2);
            double c=y1-x1*m;
            for(j=min(x1,x2);j<=max(x1,x2);j++)
            {
                if(mx==j&&my>=m*j+c-5&&my<=m*j+c+5)
                {
                    Line=i;
                    return;
                }
            }
        }


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
        printf("%d ",History.size());
        if(History.size()>1&&Index>-1)
        {
             History.erase(History.begin()+Index);
             Index=-1;
        }
        printf("%d %d\n",History.size(),Index);
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
            pair<int,int> temp=History.back();
            if(temp.first==-1)
            {
                while(History.back().first==-1)
                {
                    History.pop_back();
                    if(History.empty()) break;
                }
                History.pop_back();
                break;
            }
            History.pop_back();
        
        }
    }
    if(key=='l')
    {
        Line=!Line;
        if(!Line) LineX=LineY=-1;
    }

    if(key=='+')
    {
        History.push_back({rand()%iScreenWidth,rand()%iScreenHeight});
    }

    if(key=='-')
    {
        if(History.size()>1)
        History.pop_back();
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
    History.push_back({500,500});
    History.push_back({1000,500});
    History.push_back({800,800});
    glutInit(&argc, argv);
    iInitialize(1920,1080,"Graph");
    glutFullScreen();
    // glutSetCursor(GLUT_CURSOR_NONE);
    glutMainLoop();
}
