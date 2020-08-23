//Headers
#include<windows.h>
#include"myWindow.h"
#define MyTimer 110


//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int iPaintFlag;
//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	//code
	//initialization of WINDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(MYICON));           //our own icon
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));		//our own icon

	//register above class
	RegisterClassEx(&wndclass);

	//create window
	hwnd = CreateWindow(szAppName,
		TEXT("Payal..MyWindow"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HBRUSH brush[8];
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	//code
	switch (iMsg)
	{	
	case WM_CREATE :

		brush[0] = CreateSolidBrush(RGB(255, 0, 0));
		brush[1] = CreateSolidBrush(RGB(0, 255, 0));
		brush[2] = CreateSolidBrush(RGB(0, 0, 255));
		brush[3] = CreateSolidBrush(RGB(0, 255, 255));
		brush[4] = CreateSolidBrush(RGB(216, 0, 115));
		brush[5] = CreateSolidBrush(RGB(255, 180, 0));
		brush[6] = CreateSolidBrush(RGB(0, 0, 0));
		brush[7] = CreateSolidBrush(RGB(255, 255, 255));

		SetTimer(hwnd, 110, 1000, NULL);
		break;

	case WM_TIMER :
		KillTimer(hwnd, 110);
		iPaintFlag++;
		if (iPaintFlag > 7)
			iPaintFlag = 0;
		InvalidateRect(hwnd, NULL, TRUE);
		SetTimer(hwnd, 110, 1000, NULL);

		break;
	case WM_PAINT :
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd,&ps);
		SelectObject(hdc, brush[iPaintFlag]);
		FillRect(hdc, &rc, brush[iPaintFlag]);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}