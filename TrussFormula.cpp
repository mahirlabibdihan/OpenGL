#include <iostream>
using nam
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
	cout<<FX<<endl;
}

int main(int argc,char *argv[])
{
	Calculate();
}