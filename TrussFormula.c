#include <stdio.h>
#define MAX 3
struct Truss
{
	float x,y;
	float Lx,Ly;
	int Sx,Sy;
	int n;
	int Adj[10];
}Node[10];

int n;

void Equilibrium()
{
	int i,j;
	float FX=0,FY=0;
	for(i=0;i<n;i++)
	{
		FX+=Node[i].Lx;
		FY+=Node[i].Ly;
	}

	puts("          ^");
	puts("X ->    y |");
	
	for(i=0;i<n;i++)
	{
		if(Node[i].Sx+Node[i].Sy==2)
		{		
			float M=0;
			for(j=0;j<n;j++)
			{
				M+=(Node[i].x-Node[j].x)*Node[j].Ly;
				M-=(Node[i].y-Node[j].y)*Node[j].Lx;			
			}
			printf("FX = %f FY = %f M = %f\n",FX,FY,M);

			for(j=0;j<n;j++)
			{
				if(Node[j].Sx+Node[j].Sy==1)
				{
					if(Node[j].Sy)
					{
						Node[i].Lx-=FX;
						Node[j].Ly-=M/(Node[i].x-Node[j].x);
						Node[i].Ly+=M/(Node[i].x-Node[j].x)-FY;
						printf("FX1 = %f FY1 = %f\nFY2 = %f",-FX,M/(Node[i].x-Node[j].x)-FY,-M/(Node[i].x-Node[j].x));
					}
					else
					{
						Node[i].Ly-=FY;
						Node[j].Lx-=M/(Node[i].y-Node[j].y);
						Node[i].Lx+=M/(Node[i].y-Node[j].y)-FX;
						printf("FY1 = %f FX1 = %f\nFX2 = %f",-FY,M/(Node[i].y-Node[j].y)-FX,-M/(Node[i].y-Node[j].y));
					}					
				}		
			}			
		}
	}
}


int main()
{
	int i;
	scanf("%d",&n);
	
	for(i=0;i<n;i++)
	{
		printf("Node %d : ",i+1);
		scanf("%f %f %f %f %d %d",&Node[i].x,&Node[i].y,&Node[i].Lx,&Node[i].Ly,&Node[i].Sx,&Node[i].Sy);
		// while((getchar()) != '\n');
	}
	Equilibrium();
}

/*
	7
	0 0 0 -1.5 1 1
	2.25 1 0 -3 0 0
	3 0 0 0 0 0
	4.5 2 0 -3 0 0
	6 0 0 0 0 0
	6.75 1 0 -3 0 0
	9 0 0 -1.5 0 1
*/