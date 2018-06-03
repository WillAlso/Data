#include <iostream>
using namespace std;
#define MAXSIZE 50
void Input(double x[MAXSIZE],double y[MAXSIZE],long n)
{
	long i;
	for(i = 0;i <= n - 1;i++)
	{
		cout << "请输入插入节点:x[" << i << "]y[" << i << "]:"; 
		cin >> x[i] >> y[i];
	}
}
int main()
{
	double x[MAXSIZE],y[MAXSIZE],_x,_y,t;
	long n,i,j;
	cout << "请输入插值节点的个数:";
	cin >> n;
	Input(x,y,n);
	cout << "请输入插值点:";
	cin >> _x;
	_y = 0;
	for(i = 0;i <= n - 1;i++)
	{
		t = 1;
		for(j = 0;j <= n - 1;j++)
		{
			if(j != i)
			{
				t *= (_x - x[j]) / (x[i] - x[j]);
			}
		}
		_y += t * y[i];
	}
	cout << "插值点(x,y) = (" << _x << ")(" << _y << ")" << endl;
	return 0;
}