#include<windows.h>
int nMode;
RECT rect;
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain
(
 HINSTANCE hinstaance,
 HINSTANCE pre,LPSTR lpszCmdLine,
 int nCmdShow
 )
{
 	HWND hwnd;
 	MSG msg;
 	WNDCLASS wndclass;
	char lpszClassName[]=" ";
	char Title[]="สตั้ศý";
	wndclass.cbClsExtra=0;
	wndclass.cbWndExtra=0;
 	wndclass.hbrBackground=CreateSolidBrush(RGB(255,255,255));
	wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndclass.hIcon=LoadIcon(NULL,IDI_QUESTION);
	wndclass.hInstance=hinstaance;
	wndclass.lpfnWndProc=WndProc;
	wndclass.lpszClassName=lpszClassName;
	wndclass.lpszMenuName=NULL;
	wndclass.style=0;
	RegisterClass(&wndclass);
 	hwnd=CreateWindow(lpszClassName,Title,WS_OVERLAPPEDWINDOW|WS_HSCROLL|WS_VSCROLL,100,100,500,500,NULL,NULL,hinstaance,NULL );
 	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0))
 	{
 	 	TranslateMessage(&msg);
 	 	DispatchMessage(&msg);
 	}
 	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
 	HDC hdc;
 	HPEN hp;
 	HBRUSH hb;
 	static int Circle;
	static int s;
	PAINTSTRUCT ps;
	switch(message) {
 	  case WM_KEYDOWN:
 	 	if(wParam==VK_CONTROL)
 	 	{
 	 	 	Circle=1;
			s = 0;
			rect.left=0;
 	 	 	rect.right=50;
			rect.top=0;
 	 	 	rect.bottom=50;
            InvalidateRect(hwnd,NULL,1);
 	 	}else if(wParam == VK_SHIFT)
		{
			Circle=0;
			s = 1;
			rect.left=0;
 	 	 	rect.right=50;
			rect.top=0;
 	 	 	rect.bottom=50;
			InvalidateRect(hwnd,NULL,1);
		}
 	 	else if(wParam==VK_HOME)
 	 	{
 	 	 	rect.left=rect.left-10;
			rect.right=rect.right-10;
 	 	 	if(Circle==1)
 	 	 	{
 	 	 	 	InvalidateRect(hwnd,NULL,1);
 	 	 	}
 	 	}
 	 	else if(wParam==VK_END)
 	 	{
 	 	 	rect.left=rect.left+10;
			rect.right=rect.right+10;
 	 	 	if(Circle==1)
 	 	 	{
 	 	 	 	InvalidateRect(hwnd,NULL,1);
 	 	 	}
		}else if(wParam == VK_RIGHT)
		{
			rect.right = rect.right + 10;
			if(s == 1)
			{
				InvalidateRect(hwnd,NULL,1);
			}
		}else if(wParam == VK_LEFT)
		{
			rect.bottom = rect.bottom + 10;
			if(s == 1)
			{
				InvalidateRect(hwnd,NULL,1);
			}
		}else if(wParam == VK_PRIOR)
		{
			rect.top = rect.top - 10;
			rect.bottom = rect.bottom - 10;
			if(s == 1)
			{
				InvalidateRect(hwnd,NULL,1);
			}
		}else if(wParam == VK_NEXT)
		{
			rect.top = rect.top + 10;
			rect.bottom = rect.bottom + 10;
			if(s == 1)
			{
				InvalidateRect(hwnd,NULL,1);
			}
		}
 	 	break;
	  case WM_PAINT:
 	 	hdc=BeginPaint(hwnd,&ps);
		SetMapMode(hdc,MM_ISOTROPIC);
 	 	SetWindowExtEx(hdc,1,1,NULL);
		SetViewportExtEx(hdc,1,1,NULL);
		hp=CreatePen(PS_SOLID,0,RGB(0,0,255));
		hb=CreateSolidBrush(RGB(0,255,0));
        SelectObject(hdc,hb);
		SelectObject(hdc,hp);
		if(Circle==1)
 	 	{
 	 	 	Ellipse(hdc,rect.left,rect.top,rect.right,rect.bottom);
 	 	} else if(s == 1)
		{
			Rectangle(hdc,rect.left,rect.top,rect.right,rect.bottom);
		}
 	 	EndPaint(hwnd,&ps);
	 	break;
	  case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
 	 	return(DefWindowProc(hwnd,message,wParam,lParam));
 	}
 	return 0;
}
