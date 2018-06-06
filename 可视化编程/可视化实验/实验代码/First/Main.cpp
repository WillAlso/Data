#include <windows.h>

int colorFlag = 0;

LRESULT CALLBACK WinSunProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	WNDCLASS wndcls;
	wndcls.cbClsExtra=0;
	wndcls.cbWndExtra=0;
	HBRUSH hB; 
	hB=CreateSolidBrush(RGB(50,20,200));
	//wndcls.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wndcls.hbrBackground=hB;
	wndcls.hCursor=LoadCursor(NULL,IDC_CROSS);
	wndcls.hIcon=LoadIcon(NULL,IDI_ERROR);
	wndcls.hInstance=hInstance;
	wndcls.lpfnWndProc=WinSunProc;
	wndcls.lpszClassName = "WHUT";
	wndcls.lpszMenuName=NULL;
	wndcls.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndcls);
	HWND hwnd;
	hwnd = CreateWindow("WHUT","武汉理工大学计算机学院",WS_OVERLAPPEDWINDOW,0,0,600,400,NULL,NULL,hInstance,NULL);
	SetTimer(hwnd,1000,1000,NULL);
	ShowWindow(hwnd,SW_SHOWNORMAL);
	UpdateWindow(hwnd);
	MSG msg;
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WinSunProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	HDC hdc;
	HBRUSH hb1,hb2,hb3;
	PAINTSTRUCT ps;
	switch(uMsg)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd,&ps);
		SetMapMode(hdc,MM_TEXT);
		hb1 = CreateSolidBrush(RGB(255,0,0));
		hb2 = CreateSolidBrush(RGB(0,255,0));
		hb3 = CreateSolidBrush(RGB(0,0,255));
		if(colorFlag == 0)
		{
			SelectObject(hdc,hb1);
			Rectangle(hdc,0,0,800,800);
		}else if(colorFlag == 1)
		{
			SelectObject(hdc,hb2);
			Rectangle(hdc,0,0,800,800);
		}else if(colorFlag == 2)
		{
			SelectObject(hdc,hb3);
			Rectangle(hdc,0,0,800,800);
		}
		EndPaint(hwnd,&ps);
		DeleteObject(hb1);
		DeleteObject(hb2);
		DeleteObject(hb3);
		break;
	case WM_TIMER:
		if(wParam == 1000)
        {
            colorFlag = (colorFlag + 1)%3;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;
	case WM_CLOSE:
		if(IDYES == MessageBox(hwnd,"是否真的结束?","whut",MB_YESNO))
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY:
		KillTimer(hwnd, 1000);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd,uMsg,wParam,lParam);
	}
	return 0;
}
