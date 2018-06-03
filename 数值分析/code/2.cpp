#include <iostream>
using namespace std;

#define MAXSIZE 50

void Input(double a[MAXSIZE][MAXSIZE],long n)
{
	long i,j;
	cout << "输入源方程组的增广矩阵:" << endl;
	for(i = 1;i <= n;i++)
	{
		for(j = 1;j <= n + 1;j++)
		{
			cin >> a[i][j];
		}
	}
}
void Output(double x[MAXSIZE],long n)
{
	long k;
	cout << "原方程组的解为:" << endl;
	for(k = 1;k <= n;k++)
	{
		cout << x[k - 1] << " ";
	}
	cout << endl;
}
int main()
{
	double a[MAXSIZE][MAXSIZE],x[MAXSIZE],s;
	long n,i,j,k;
	cout << "请输入原方程组阶数:";
	cin >> n;
	Input(a,n);
	for(k = 0;k <= n - 2;k++)
	{
		for(i = k + 1;i <= n - 1;i++)
		{
			a[i][k] /= a[k][k];
			for(j = k + 1;j <= n;j++)
			{
				a[i][j] += a[i][k] * a[k][j];
			}
		}
	}
	for(k = n - 1;k >= 0;k--)
	{
		s = 0;
		for(j = k+ 1;j <= n - 1;j++)
		{
			s += a[k][j] * x[j];
		}
		x[k] = (a[k][n] - s) / a[k][k];
	}
	Output(x,n);
	return 0;
}
