#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI acos(-1)
#define max(a,b) (a>b?a:b)
typedef struct
{
	double Magnitude , Angle ; 
}Force;

double Sqrt(double n)
{
	double l=0.0,r=max(n,1),m=0;
	if(n<0) 
	{
		puts("Root of negative number not possible.");
		return 0;
	}
	while(r-l>.000000001)
	{
		double temp=(l+r)/2;
		if(m==temp) break;
		m=temp;
		if(m*m>n) r=m;
		else l=m;
	}

	return m;
} 


int main()
{
	int n;
	printf("Number of Forces : ");
	scanf("%d",&n);

	int i;
	Force *F=(Force*)malloc(sizeof(Force)*n);
	for(i=0;i<n;i++)
	{
		scanf("%lf %lf",&F[i].Magnitude,&F[i].Angle);
		F[i].Angle = F[i].Angle * PI / 180 ;
	}

	double Rx=0,Ry=0;

	for(i=0;i<n;i++)
	{
		Rx+=F[i].Magnitude*cos(F[i].Angle);
		Ry+=F[i].Magnitude*sin(F[i].Angle);
	}

	double R = Sqrt(Rx*Rx+Ry*Ry);
	double Theta = atan(Ry/Rx) * 180 / PI;

	printf("%lf %lf\n",R,Theta);
}