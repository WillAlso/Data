#include <iostream>
#include "Tourism.h"
using namespace std;
int main()
{
	int bRunning = -1;
	while(bRunning)
	{
		cout << "====景区信息管理系统====" << endl;
		cout << "1.创建景区景点图" << endl;
		cout << "2.查询景点信息" << endl;
		cout << "3.旅游景点导航" << endl;
		cout << "4.搜索最短路径" << endl;
		cout << "5.铺设电路规划" << endl;
		cout << "0.退出" << endl;
		cin >> bRunning;
		switch(bRunning)
		{
		case 1:
			{
				system("cls");
				CreateGraph();
				break;
			}
		case 2:
			{
				system("cls");
				GetSpotInfo();
				break;
			}
		case 3:
			{
				TravelPath();
				break;
			}
		case 4:
			{
				break;
			}
		case 5:
			{
				break;
			}
		case 0:
			{
				break;
			}
		default:
			{
				if(bRunning != 0)
				{
					cout << "输入选项有误!" << endl;
				}
				break;
			}
		}
	}
	return 0;
}