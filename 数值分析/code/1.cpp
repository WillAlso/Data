#include <iostream>
#include <cmath> 
using namespace std;
double fun(double x)
{
	return (2 * x * x * x - 9 * x - 25);
}
double dfun(double x)
{
	return (6 * x * x - 9);
}
int main()
{
	long cnt,i;
	double e,x0,x1,f1,f2;
	cout << "输入迭代初值:";
	cin >> x0;
	cout << "输入精度要求:";
	cin >> e;
	cout << "输入最大迭代次数:";
	cin >> cnt;
	for(i = 0;i < cnt;i++)
	{
		x1 = x0;
		f1 = fun(x1);
		f2 = dfun(x1);
		x0 = x1 - f1 / f2;
		if(abs(x1 - x0) <= e)
		{
			break;
		}
	}
	if(i < cnt)
	{
		cout << "结果:" << x0 << endl;
	}else{
		cout << "迭代超数!" << endl;
	}
	return 0;
}
