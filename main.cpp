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
#include<string.h>
using namespace std;
#define HEIGHT 1080
#define WIDTH 1920
#define min(a,b)  (a<b?(a):(b))
#define max(a,b)  (a>b?(a):(b))


typedef struct {
	double Real,Imag;
}Complex;

typedef struct {
	char Real[20]={},Imag[20]={};
}ComplexString;

Complex x[2][2];
Complex y[2][1];


Complex X,Y;
ComplexString C={},D={};

Complex p[3];
ComplexString P[3];

ComplexString A[2][2];
ComplexString B[2][1];


int Pos=0,Calc=0;

int Activei=0,Activej=0;
/*
	function iDraw() is called again and again by the system.
*/



double AbsF(double n)
{
	return n<0?-n:n;
}

Complex CMul(Complex z1,Complex z2)
{
	return {z1.Real*z2.Real-z1.Imag*z2.Imag,z1.Real*z2.Imag+z1.Imag*z2.Real};
}



Complex CAdd(Complex z1,Complex z2)
{
	return {z1.Real+z2.Real,z1.Imag+z2.Imag};
}

Complex CSub(Complex z1,Complex z2)
{
	return {z1.Real-z2.Real,z1.Imag-z2.Imag};
}

Complex Determinant(Complex x[2][2])
{
	return CSub(CMul(x[0][0],x[1][1]),CMul(x[0][1],x[1][0]));
}

Complex CDiv(Complex z1,Complex z2)
{
      if (z2.Real == 0 && z2.Imag == 0)
      {
      	return {0,0};
      }
      else
      {

      	double x,y,z;
        x = z1.Real*z2.Real + z1.Imag*z2.Imag;
        y = z1.Imag*z2.Real - z1.Real*z2.Imag;
        z = z2.Real*z2.Real + z2.Imag*z2.Imag;
        printf("%lf %lf %lf\n",x,y,z);
       	return {x/z,y/z};
      }

}
void Equation()
{
    Complex det[3];
    int i, j, k;

    det[0] = Determinant(x);

    if(!det[0].Real&&!det[0].Imag)
    {
        X=Y={0,0};
        p[0]=p[1]=p[2]={0,0};
        return;
    }
    p[0]=det[0];

    for (i = 1; i <= 2; i++)
    {
        Complex temp[2][2];
        for (j = 0; j < 2; j++)
        {
            if (j != i - 1)
            {
                for (k = 0; k < 2; k++)
                {
                    temp[j][k]=x[j][k];
                }
            }

            else
            {
                for(k=0;k<2;k++)
                {
                    temp[j][k]=y[k][0];
                }
            }
        }
        det[i]=Determinant(temp);
        p[i]=det[i];

    }

    X=CDiv(det[1],det[0]);
    Y=CDiv(det[2],det[0]);
}


void iDraw(void)
{
    iClear();

    if(Pos==0)iSetColor(255,255,255);
    else iSetColor(100,100,100);
    iRectangle(2,940,550,120);
    iBigText(10,950,A[0][0].Real);

    if(Pos==1)iSetColor(255,255,255);
    else iSetColor(100,100,100);
    iRectangle(2,818,550,120);
    iBigText(10,830,A[0][0].Imag);

    if(Pos==6)iSetColor(255,255,255);
    else iSetColor(100,100,100);
    iRectangle(2,660,550,120);
    iBigText(10,670,A[1][0].Real);

    if(Pos==7)iSetColor(255,255,255);
    else iSetColor(100,100,100);
    iRectangle(2,538,550,120);
    iBigText(10,550,A[1][0].Imag);



    if(Pos==2)iSetColor(255,255,255);
    else iSetColor(100,100,100);
    iRectangle(710,940,550,120);
    iBigText(718,950,A[0][1].Real);

    if(Pos==3)iSetColor(255,255,255);
    else iSetColor(100,100,100);
    iRectangle(710,818,550,120);
    iBigText(718,830,A[0][1].Imag);

    if(Pos==8)iSetColor(255,255,255);
    else iSetColor(100,100,100);
    iRectangle(710,660,550,120);
    iBigText(718,670,A[1][1].Real);

    if(Pos==9)iSetColor(255,255,255);
    else iSetColor(100,100,100);
    iRectangle(710,538,550,120);
    iBigText(718,550,A[1][1].Imag);

    if(Pos==4)iSetColor(255,255,255);
    else iSetColor(100,100,100);
    iRectangle(1360,940,550,120);
    iBigText(1368,950,B[0][0].Real);

    if(Pos==5)iSetColor(255,255,255);
    else iSetColor(100,100,100);
    iRectangle(1360,818,550,120);
    iBigText(1368,830,B[0][0].Imag);



    if(Pos==10)iSetColor(255,255,255);
    else iSetColor(100,100,100);
    iRectangle(1360,660,550,120);
    iBigText(1368,670,B[1][0].Real);

    if(Pos==11)iSetColor(255,255,255);
    else iSetColor(100,100,100);
    iRectangle(1360,538,550,120);
    iBigText(1368,550,B[1][0].Imag);


    if(Pos==12)iSetColor(255,255,255);
    else iSetColor(100,100,100);
    iRectangle(200,300,1300,200);
    iRectangle(200,50,1300,200);

    sprintf(C.Real,"%.5lf",X.Real);
    sprintf(C.Imag,"%.5lf",X.Imag);
    sprintf(D.Real,"%.5lf",Y.Real);
    sprintf(D.Imag,"%.5lf",Y.Imag);

    sprintf(P[0].Real,"%.5lf",p[0].Real);
    sprintf(P[0].Imag,"%.5lf",p[0].Imag);
    sprintf(P[1].Real,"%.5lf",p[1].Real);
    sprintf(P[1].Imag,"%.5lf",p[1].Imag);
    sprintf(P[2].Real,"%.5lf",p[2].Real);
    sprintf(P[2].Imag,"%.5lf",p[2].Imag);


    iBigText(208,340,C.Real);
    iBigText(850,340,C.Imag);

    iBigText(208,90,D.Real);
    iBigText(850,90,D.Imag);

    iBigText(580,900,"+");
    iBigText(580,620,"+");
    iBigText(1260,900,"=");
    iBigText(1260,620,"=");
    iBigText(2,350,"X=");
    iBigText(2,100,"Y=");



    iTriangle(1520,30,1540,60,1560,30);
    iTriangle(1520,130,1540,160,1560,130);
    iTriangle(1520,230,1540,260,1560,230);

    iText(1600,240,P[0].Real);
    iText(1770,240,P[0].Imag);
    iText(1580,240,"=");
    iText(1580,140,"=");
    iText(1580,40,"=");

    iText(1600,140,P[1].Real);
    iText(1770,140,P[1].Imag);
    iText(1560,120,"1");
    iText(1560,20,"2");


    iText(1600,40,P[2].Real);
    iText(1770,40,P[2].Imag);

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
    if(key==27) exit(0);
    if(key=='\r')
    {
        if(Pos<12) Pos++;
    }

    else if(key=='\b')
    {
        if(Pos==12) Pos--;
        if(Pos==4||Pos==5||Pos==10||Pos==11)
        {
            if(Pos%2==0)
            {
                if(strlen(B[Pos/6][0].Real)==0)
                {
                    if(Pos>0) Pos--;
                    return;
                }
                B[Pos/6][0].Real[strlen(B[Pos/6][0].Real)-1]='\0';
            }
            else
            {
                if(strlen(B[Pos/6][0].Imag)==0)
                {
                    if(Pos>0) Pos--;
                    return;
                }
                B[Pos/6][0].Imag[strlen(B[Pos/6][0].Imag)-1]='\0';
            }
        }

        else
        {

            if(Pos%2==0)
            {
                if(strlen(A[Pos/6][(Pos/2)%3].Real)==0)
                {
                    if(Pos>0) Pos--;
                    return;
                }
                A[Pos/6][(Pos/2)%3].Real[strlen(A[Pos/6][(Pos/2)%3].Real)-1]='\0';
            }

            else
            {
                if(strlen(A[Pos/6][(Pos/2)%3].Imag)==0)
                {
                    if(Pos>0) Pos--;
                    return;
                }
                A[Pos/6][(Pos/2)%3].Imag[strlen(A[Pos/6][(Pos/2)%3].Imag)-1]='\0';
            }
        }
    }

    else
    {
        if(Pos==12) return;
        if(Pos==4||Pos==5||Pos==10||Pos==11)
        {
             if(Pos%2==0)
            {
                int sz=strlen(B[Pos/6][0].Real);
                B[Pos/6][0].Real[sz]=key;
                B[Pos/6][0].Real[sz+1]='\0';
            }

            else
            {
                int sz=strlen(B[Pos/6][0].Imag);
                B[Pos/6][0].Imag[sz]=key;
                B[Pos/6][0].Imag[sz+1]='\0';
            }
        }
        else
        {
            if(Pos%2==0)
            {
                int sz=strlen(A[Pos/6][(Pos/2)%3].Real);
                A[Pos/6][(Pos/2)%3].Real[sz]=key;
                A[Pos/6][(Pos/2)%3].Real[sz+1]='\0';
            }

            else
            {
                int sz=strlen(A[Pos/6][(Pos/2)%3].Imag);
                A[Pos/6][(Pos/2)%3].Imag[sz]=key;
                A[Pos/6][(Pos/2)%3].Imag[sz+1]='\0';
            }
        }

    }
}


void iSpecialKeyboard(unsigned char key)
{
    if(key==GLUT_KEY_END)
    {
        exit(0);
    }

    if(key==GLUT_KEY_LEFT)
    {
        if(Pos>0)
        {
            if(Pos%6==1) Pos+=3;
            else if(Pos==6) Pos--;
            else Pos-=2;
        }
        else Pos=11;
    }

    if(key==GLUT_KEY_UP)
    {
        if(Pos>=0)
        {
            if(Pos%2) Pos--;
            else if(Pos>4) Pos-=5;
            else Pos+=7;
        }
    }

    if(key==GLUT_KEY_DOWN)
    {
        if(Pos<12)
        {
            if(Pos%2==0) Pos++;
            else if(Pos<7) Pos+=5;
            else Pos-=7;
        }
    }

    if(key==GLUT_KEY_RIGHT)
    {
        if(Pos<11)
        {
            if(Pos%6==4) Pos-=3;
            else if(Pos==5) Pos++;
            else Pos+=2;
        }
        else Pos=0;
    }
}



void Calculator()
{
    int i,j;
    for(i=0;i<2;i++)
    {
        for(j=0;j<3;j++)
        {
             if(sscanf(A[i][j].Real,"%lf",&x[i][j].Real)==EOF) x[i][j].Real=0;
             if(sscanf(A[i][j].Imag,"%lf",&x[i][j].Imag)==EOF) x[i][j].Imag=0;
        }
    }

    for(i=0;i<2;i++)
    {
        if(sscanf(B[i][0].Real,"%lf",&y[i][0].Real)==EOF) y[i][0].Real=0;
        if(sscanf(B[i][0].Imag,"%lf",&y[i][0].Imag)==EOF) y[i][0].Imag=0;
    }
    Equation();
}

int main(int argc,char *argv[])
{
    iSetTimer(0,Calculator);
    glutInit(&argc, argv);
    iInitialize(1920,1080,"AC");
}
