#include "iGraphics.h"
/*
 ______   _________ _      _       _
|  ____ \|___   ___| |    | |     | |
| |    \ \   | |   | |____| |     | |
| |    | |   | |   |  ____  |     | |
| |____/ /___| |___| |    | |_____| |
|_______/|_________|_|    |_________|
M A H I R     L A B I B     D I H A N

*/



/*
###########################
(

)

+	-> Add

-	-> Substract

*	-> Multiply

/	-> Divide
	
%	-> Modulas

^	-> Power

!	-> Factorial

p	-> nPr

c 	-> nCr

l 	-> LCM

g 	-> GCD

&	-> And
	
|	-> Or

exit ->  Exit
###########################

*/

#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
double Bodmash(string);

char Graph[2100][1300];

int main(int argc,char *argv[])
{	
	string LHS="y",RHS=".001*x^2";
	cout<<": ";
	getline(cin, LHS ,'=');
	getline(cin , RHS );

	// cout<<LHS<<" "<<RHS<<endl;
	
	int i,j,k;
	for(i=0;i<1920;i++)
	{
			string temp1=LHS;
			for(j=0;j<temp1.size();j++)
			{
				if(temp1[j]=='x')
				{

					temp1.erase(temp1.begin()+j);
					if(i>960)
						temp1.insert(j,"("+to_string(i-960)+")");
					else
						temp1.insert(j,"(0"+to_string(i-960)+")");
				}
			}

			string temp2=RHS;
			for(j=0;j<temp2.size();j++)
			{
				if(temp2[j]=='x')
				{
					temp2.erase(temp2.begin()+j);
					if(i>960)
						temp2.insert(j,"("+to_string(i-960)+")");
					else
						temp2.insert(j,"(0"+to_string(i-960)+")");
				}
			}


		for(k=0;k<1080;k++)
		{

			if(Graph[i][k]) break;
			string temp3=temp1;
			for(j=0;j<temp3.size();j++)
			{
				if(temp3[j]=='y')
				{
					temp3.erase(temp3.begin()+j);
					if(k>540)
						temp3.insert(j,"("+to_string(k-540)+")");
					else
						temp3.insert(j,"(0"+to_string(k-540)+")");
				}
			}

			string temp4=temp2;
			for(j=0;j<temp4.size();j++)
			{
				if(temp4[j]=='y')
				{
					temp4.erase(temp4.begin()+j);
					if(k>540)
						temp4.insert(j,"("+to_string(k-540)+")");
					else
						temp4.insert(j,"(0"+to_string(k-540)+")");
				}
			}
			

			double x,y;
			double y1,y2;

			y1=Bodmash(temp3);
			y2=Bodmash(temp4);


			
			if(fabs(y1-y2)<0.5)
			{
				cout<<y1<<" "<<y2<<endl;
				x=i;
				y=k;	
				if(y>=0 && y < 1080) Graph[(int)x][(int)(y)]=1;
				break;
			}
		}
	}

	for(i=0;i<1080;i++)
	{
			string temp1=LHS;
			for(j=0;j<temp1.size();j++)
			{
				if(temp1[j]=='y')
				{

					temp1.erase(temp1.begin()+j);
					if(i>540)
						temp1.insert(j,"("+to_string(i-540)+")");
					else
						temp1.insert(j,"(0"+to_string(i-540)+")");
				}
			}

			string temp2=RHS;
			for(j=0;j<temp2.size();j++)
			{
				if(temp2[j]=='y')
				{
					temp2.erase(temp2.begin()+j);
					if(i>540)
						temp2.insert(j,"("+to_string(i-540)+")");
					else
						temp2.insert(j,"(0"+to_string(i-540)+")");
				}
			}

		for(k=0;k<1920;k++)
		{
			if(Graph[k][i]) break;
			string temp3=temp1;
			for(j=0;j<temp3.size();j++)
			{
				if(temp3[j]=='x')
				{
					temp3.erase(temp3.begin()+j);
					if(k>960)
						temp3.insert(j,"("+to_string(k-960)+")");
					else
						temp3.insert(j,"(0"+to_string(k-960)+")");
				}
			}

			string temp4=temp2;
			for(j=0;j<temp4.size();j++)
			{
				if(temp4[j]=='x')
				{
					temp4.erase(temp4.begin()+j);
					if(k>960)
						temp4.insert(j,"("+to_string(k-960)+")");
					else
						temp4.insert(j,"(0"+to_string(k-960)+")");
				}
			}
			

			double x,y;
			double x1,x2;

			x1=Bodmash(temp3);
			x2=Bodmash(temp4);


			
			if(fabs(x1-x2)<0.5)
			{
				cout<<x1<<" "<<x2<<endl;
				y=i;
				x=k;	
				if(x>=0 && x < 1920) Graph[(int)x][(int)(y)]=1;
				break;
			}
		}
	}

	glutInit(&argc, argv);
    iInitialize(1920,1080,"iGraphics");
    // glutFullScreen();
    glutMainLoop();
}


string Trim(string a)
{
	if (a == "∞") return a;
	string Int, Frac;
	int i, n = a.length();

	for (i = 0; i < n; i++)
	{
		if (a[i] == '.') break;
		Int += a[i];
	}
	for (; i < n; i++)
	{
		Frac += a[i];
	}

	if (Int[0] == '-')
		while (Int.length() > 0 && Int[0] == '0')
		{
			Int.erase(Int.begin() + 1);
		}

	else
		while (Int.length() > 0 && Int[0] == '0')
		{
			Int.erase(Int.begin());
		}

	while (Frac.length() > 0 && Frac.back() == '0')
	{
		Frac.pop_back();
	}
	if (Frac.length() > 0 && Frac.back() == '.')
	{
		Frac.pop_back();
	}

	string Number = Int + Frac;
	if (Number.length() > 0) return Number;
	return "0";
}

double binaryExponentiation(double x,int n)
{
    if(n==0) return 1;
    else if(n%2 == 0) return binaryExponentiation(x*x,n/2);
    else return x*binaryExponentiation(x*x,(n-1)/2);
}

double Root(double n,double x)
{
	if(n<0) return -1;
	double l = 0, r = n, m = 0;
	if (n<=1) r = 1;
	while (r-l>.000000000001)
	{
		double temp = (l+r)/2;
		if (m==temp)
		{
			break;
		}
		m = temp;
		(binaryExponentiation(m,x)>n)? r = m : l = m;
	}
	return m;
}

pair<double,double> Fraction(double s)
{
	double WholeNum = s ,DecNum=1;

	int i,j;

	while(WholeNum-int(WholeNum)>.0000001)
	{	
		WholeNum*=10;
		DecNum*=10;

	}

	for (i =2; i<=WholeNum ;i++)
	{
		if (fmod(WholeNum , i)== 0 && fmod(DecNum , i)== 0)
		{
			WholeNum /= i;
			DecNum /=i ;
		}
	}
	return {WholeNum,DecNum}; 
}

double Power(double Number,double Power)
{
	pair<double,double> Num(Fraction(Power));
	Number =binaryExponentiation(Number, Num.first);
	if (Num.second> 1) return Root(Number,Num.second);
	return Number;
}





bool hasPrecedence(char op1, char op2) 
{
	if (op2 == '(' || op2 == ')')
		return false;
	if ((op1 == '^' || op1 == '*' || op1 == '/' ) && (op2 == '+' || op2 == '-'))
		return false;
	if ((op1 == '^' ) && (op2 == '*' || op2 == '/' ))
		return false;
	else
		return true;
}

long double binaryExponentiation(long double x,int n)
{
    if(n==0) return 1;
    else if(n%2 == 0) return binaryExponentiation(x*x,n/2);
    else return x*binaryExponentiation(x*x,(n-1)/2);
}

double applyOp(char op, double B,double A) 
{
	switch (op) {
	case '+':
		return A+B;
		break;
	case '-':
		return A-B;
		break;
	case '*':
		return A*B;
		break;
	case '^':
		return Power(A,B);
		break;
	case '%': fmod(A,B);
		break;
	case '/': A/B;
		break;
	}
	return 0;
}

double Bodmash(string expression)
{
	if (expression.length() == 0) return 0;


	stack<double> values;
	stack<char> ops;

	for (int i = 0; i < expression.length(); i++)
	{
		if(expression[i]==' ') continue;
		if ((expression[i] >= '0' && expression[i] <= '9') || expression[i] == '.') {
			string num = "";
			while (i < expression.length() && (expression[i] >= '0' && expression[i] <= '9' || expression[i] == '.'))
				num += expression[i++];
			i--;
			values.push(stod(num));
		}
		else if (expression[i] == '(') ops.push(expression[i]);

		else if (expression[i] == ')') {
			while (ops.top() != '(') {
				double value1, value2;
				if (!values.empty()) {
					value1 = values.top();
					values.pop();
				}
				else value1 = 0;
				if (!values.empty()) {
					value2 = values.top();
					values.pop();
				} else value2 = 0;
				values.push(applyOp(ops.top(), value1, value2));
				ops.pop();
			}
			ops.pop();
		}

		else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '%' || expression[i] == '^' ||expression[i] == 'p' ||expression[i] == 'c' ||expression[i] == 'g' ||expression[i] == 'l' ||expression[i] == '&' ||expression[i] == '|'  )
		 {
			while (!ops.empty() && hasPrecedence(expression[i], ops.top())) {
				double value1, value2;
				if (!values.empty()) {
					value1 = values.top();
					values.pop();
				}
				else value1 = 0;
				if (!values.empty()) {
					value2 = values.top();
					values.pop();
				} else value2 = 0;
				values.push(applyOp(ops.top(), value1, value2));
				ops.pop();
			}
			ops.push(expression[i]);
		}

		else if (expression[i] == '!')
		{
			while (!ops.empty() && hasPrecedence(expression[i], ops.top()))
			{
				double value = values.top();
				values.pop();
				values.push(applyOp(ops.top(), value, value));
				ops.pop();
			}
			ops.push(expression[i]);
		}
	}

	while (!ops.empty()) {
		double value1, value2;
		if (!values.empty()) {
			value1 = values.top();
			values.pop();
		}
		else value1 = 0;
		if (!values.empty()) {
			value2 = values.top();
			values.pop();
		} else
			value2 = 0;
		values.push(applyOp(ops.top(), value1, value2));
		ops.pop();
	}
	double Decimal = values.top();
	values.pop();
	// System.out.println(FromDecimal(Decimal,To));
	return Decimal;
}







void iDraw(void)
{
    iClear();

    int i,j;

    glBegin(GL_LINE_STRIP);
    for(i=960;i<2000;i++)
    {
    	for(j=540;j<1200;j++)
    	{
    		if(Graph[i][j])
    		{
    			glVertex2f(i,j);
    		}
    	}
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for(i=960;i<2000;i++)
    {
    	for(j=0;j<=540;j++)
    	{
    		if(Graph[i][j])
    		{
    			glVertex2f(i,j);
    		}
    	}
    }
    glEnd();


    glBegin(GL_LINE_STRIP);
    for(i=0;i<=960;i++)
    {
    	for(j=540;j<1200;j++)
    	{
    		if(Graph[i][j])
    		{
    			glVertex2f(i,j);
    		}
    	}
    }
    glEnd();


    glBegin(GL_LINE_STRIP);
    for(i=0;i<=960;i++)
    {
    	for(j=0;j<=540;j++)
    	{
    		if(Graph[i][j])
    		{
    			glVertex2f(i,j);
    		}
    	}
    }
    glEnd();


    iDashedLine(0,540,1920,540);
    iDashedLine(960,0,960,1080);

   	iDashedLine(0,50,1920,50);
    iDashedLine(50,0,50,1080);
    iDashedLine(0,1030,1920,1030);
    iDashedLine(1870,0,1870,1080);
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

