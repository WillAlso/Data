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
	cout << "���������ֵ:";
	cin >> x0;
	cout << "���뾫��Ҫ��:";
	cin >> e;
	cout << "��������������:";
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
		cout << "���:" << x0 << endl;
	}else{
		cout << "��������!" << endl;
	}
	return 0;
}
