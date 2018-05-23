#include <iostream>  
#include <string>
#include <cmath>
using namespace std;  

int main()  
{  
	string s1,s2;  
	int a,b,c,d,x,y,s,m;  
	while (cin >> s1 >> s2)  
	{  
		if((s1=="a1" && s2=="b2") || (s1=="b2" && s2=="a1") || (s1=="g2" && s2=="h1") || (s1=="h1" && s2=="g2"))  
		{  
			cout << "To get from " << s1 << " to " << s2 << " takes 4 knight moves." << endl;  
			continue;  
		}  
		if((s1=="a8" && s2=="b7") || (s1=="b7" && s2=="a8") || (s1=="g7" && s2=="h8") || (s1=="h8" && s2=="g7"))  
		{  
			cout << "To get from " << s1 << " to " << s2 << " takes 4 knight moves." << endl;  
			continue;  
		}  
		x=s2[0]-s1[0];    //横坐标差值  
		s=9999;  
		y=s2[1]-s1[1];    //纵坐标差值  
		for(b=-4;b<=4;b++)    //对b枚举  
		{  
			m=y+2*x-2*b+30;    //a模3的余数  
			m%=3;  
			for(a=m-6;a<=m+6;a+=3)     //对a枚举  
			{  
				c=(2*x+y-4*a-5*b)/3;    //求出c和d  
				d=(5*a+4*b-x-2*y)/3;  
				if (s>abs(a)+abs(b)+abs(c)+abs(d))  
					s=abs(a)+abs(b)+abs(c)+abs(d);     //判断是否是最小的  
			}  
		}  
		cout << "To get from " << s1 << " to " << s2 << " takes " << s << " knight moves." << endl;  
	}  
	return 0;  
}  
