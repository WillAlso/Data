#include <iostream>
#include "Tourism.h"
using namespace std;
int main()
{
	int bRunning = -1;
	while(bRunning)
	{
		cout << "====������Ϣ����ϵͳ====" << endl;
		cout << "1.������������ͼ" << endl;
		cout << "2.��ѯ������Ϣ" << endl;
		cout << "3.���ξ��㵼��" << endl;
		cout << "4.�������·��" << endl;
		cout << "5.�����·�滮" << endl;
		cout << "6.�ȵ㾰����ѯ" << endl;
		cout << "0.�˳�" << endl;
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
				system("cls");
				TravelPath();
				break;
			}
		case 4:
			{
				system("cls");
				FindShortPath();
				break;
			}
		case 5:
			{
				system("cls");
				DesignPath();
				break;
			}
		case 6:
			{
				system("cls");
				SortVex();
				break;
			}
		case 0:
			{
				system("cls");
				cout << "=====�ɹ��˳�=====" << endl;
				system("exit");
			}
		default:
			{
				if(bRunning != 0)
				{
					cout << "����ѡ������!" << endl;
				}
				break;
			}
		}
	}
	return 0;
}