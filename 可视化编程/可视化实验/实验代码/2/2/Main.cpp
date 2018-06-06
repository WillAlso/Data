//#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <afx.h>
#include "resource.h"
#define pi 3.1415926
LRESULT CALLBACK WinProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam );
int nNum=0, nMaxNum=20;

int WINAPI WinMain(
		HINSTANCE hInstance,
		HINSTANCE hPrevInstace,
		LPSTR lpCmdLine,
		int nCmdShow
		)
{
	char lpszClassName[]="����";
	char lpszTitle[]="ʵ���";
	//���һ��������
	WNDCLASS wndcls;
	wndcls.cbWndExtra=0;
	wndcls.cbClsExtra=0;
	wndcls.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wndcls.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndcls.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wndcls.hInstance=hInstance;
	wndcls.lpfnWndProc=WinProc;
	wndcls.lpszClassName=lpszClassName;
	wndcls.lpszMenuName = "MYMENU";
	wndcls.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(& wndcls);
	//�������ڣ�����һ��������������ɹ������Ĵ��ں󷵻صľ��
	HWND hwnd;
	HMENU hmenu;
	hmenu = LoadMenu(hInstance,"MYMENU");
	hwnd=CreateWindow(lpszClassName,lpszTitle,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,0,600,450,NULL,hmenu,hInstance,NULL);
	//��ʾ��ˢ�´���
	ShowWindow(hwnd ,SW_SHOWNORMAL);
	UpdateWindow(hwnd);
	//������Ϣ�ṹ�壬��ʼ��Ϣѭ��
	MSG msg;
	while(GetMessage(&msg ,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WinProc(
		HWND hwnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam
		)
{
	HBRUSH hBrush;
	HPEN hPen;
	HMENU hmenu;
	CString temp;
	LPCTSTR lpsz;
	char lpszTitle[]="My_windows";
	int x,y;    //x,y �ֱ���ΪԲ�ĵ�����
	double fAngle;
	switch(uMsg)
	{
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDM_BEGIN:
					SetTimer(hwnd,9999,100,NULL);
					break;
				case IDM_STOP:
					KillTimer(hwnd,9999);
					break;
				case IDM_EXIT:
					SendMessage(hwnd,WM_DESTROY,0,0);
					break;
			}
			break;
		case WM_CREATE:
			SetTimer(hwnd,9999,100,NULL);
			break;
		case WM_PAINT:
			HDC hDC;
			HFONT hf;
			PAINTSTRUCT ps;

			hDC=BeginPaint(hwnd ,&ps);
			SelectObject(hDC,hf);
			TEXTMETRIC tm;
			GetTextMetrics (hDC,&tm);
			temp.Format(_T("%d"), nNum);
			temp = "��ǰλ�ã�" + temp;
			lpsz = LPCTSTR(temp);
			SetTextColor(hDC,RGB(0,0,0));
			TextOut(hDC,0,0,lpsz,_tcslen(lpsz));
			SetMapMode(hDC,MM_ANISOTROPIC);
			SetWindowExtEx(hDC,400,300,NULL);       //���ô����߼���λ ����ν�߼���λ�����ڱ���һ�������ѡ���㹻�������
			SetViewportExtEx(hDC,600,450,NULL);
			SetViewportOrgEx(hDC,300,200,NULL);
			hPen=(HPEN)GetStockObject(RGB(10,100,20));   //����Բ
			SelectObject(hDC,hPen);
			Ellipse(hDC,-100,-100,100,100);
			hBrush=CreateSolidBrush(RGB(255,0,0));
			SelectObject(hDC,hBrush);
			fAngle=2*pi/nMaxNum*nNum;//���ó�ʼ�Ƕȣ�1/20*pi�� 2/20*pi��3/20*pi
			x=(int)(50*cos(fAngle));            //��ʼԲ��λ������  R (x,y)
			y=(int)(50*sin(fAngle));
			Pie(hDC,x-50,y-50,x+50,y+50,
					(int)(x+50*cos(fAngle)),(int)(y+50*sin(fAngle)),(int)(x+50*cos(fAngle+pi)),(int)(y+50*sin(fAngle+pi)) );
			hBrush=CreateSolidBrush(RGB(0,255,0));
			SelectObject(hDC,hBrush);
			fAngle=2*pi/nMaxNum*nNum; //���ó�ʼ�Ƕȣ�1/20*pi�� 2/20*pi��3/20*pi
			x=(int)(50*cos(fAngle+2*pi/3));       //��ʼԲ��λ������  R (x,y)
			y=(int)(50*sin(fAngle+2*pi/3));
			Pie(hDC,x-50,y-50,x+50,y+50,          //��֪
					(int)(x+50*cos(fAngle+2*pi/3)),
					(int)(y+50*sin(fAngle+2*pi/3)),
					(int)(x+50*cos(fAngle+pi+2*pi/3)),(int)(y+50*sin(fAngle+pi+2*pi/3)));
			hBrush=CreateSolidBrush(RGB(0,0,255));
			SelectObject(hDC,hBrush);
			fAngle=2*pi/nMaxNum*nNum;
			x=(int)(50*cos(fAngle+4*pi/3));
			y=(int)(50*sin(fAngle+4*pi/3));
			Pie(hDC,x-50,y-50,x+50,y+50,              //ͬ��
					(int)(x+50*cos(fAngle+4*pi/3)),
					(int)(y+50*sin(fAngle+4*pi/3)),
					(int)(x+50*cos(fAngle+pi+4*pi/3)),
					(int)(y+50*sin(fAngle+pi+4*pi/3)) );
			EndPaint(hwnd,&ps);
			DeleteObject(hBrush);
			DeleteObject(hPen);
			return 0;
		case WM_TIMER:
			if (wParam==9999)
			{
				nNum++;
				if (nNum > nMaxNum)     nNum = 0;
				InvalidateRect(hwnd,NULL,1);      //ˢ�¿ͻ���
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hwnd,uMsg,wParam,lParam);
	}
	return 0;
}
