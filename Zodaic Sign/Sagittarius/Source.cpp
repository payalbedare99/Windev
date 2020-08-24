//Headers
#include<windows.h>
#include"Source.h"

//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));           //our own icon
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));		//our own icon

	//register above class
	RegisterClassEx(&wndclass);

	//create window
	hwnd = CreateWindow(szAppName,
		TEXT("SAGITTARIUS..."),
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
	static HDC hdc;
	static HINSTANCE hInstance;
	PAINTSTRUCT ps;
	static RECT rc;
	static POINT pts[7];
	static long height, width;
	
	//code
	switch (iMsg)
	{
	case WM_CREATE:

		GetClientRect(hwnd, &rc);
		height = (rc.bottom - rc.top) / 10;
		width = (rc.right - rc.left) / 10 ;

		pts[0].x = rc.left + (3*width);
		pts[0].y = rc.top + (4*height);

		pts[1].x = rc.left + (width*5);
		pts[1].y = rc.top + (height*2);

		pts[2].x = rc.left + (8*width);
		pts[2].y = rc.top + (2*height);

		pts[3].x = rc.left + (7* width);
		pts[3].y = rc.top + (6* height);

		pts[4].x = rc.left + (5 * width);
		pts[4].y = rc.top + ( 8* height);

		pts[5].x = rc.left +  width;
		pts[5].y = rc.top + (9 * height);

		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		
		Ellipse(hdc, pts[0].x - 5, pts[0].y - 5, pts[0].x + 5, pts[0].y + 5);
		Ellipse(hdc, pts[1].x - 5, pts[1].y - 5, pts[1].x + 5, pts[1].y + 5);
		Ellipse(hdc, pts[2].x - 8, pts[2].y - 8, pts[2].x + 8, pts[2].y + 8);
		Ellipse(hdc, pts[3].x - 5, pts[3].y - 5, pts[3].x + 5, pts[3].y + 5);
		Ellipse(hdc, pts[4].x - 5, pts[4].y - 5, pts[4].x + 5, pts[4].y + 5);
		Ellipse(hdc, pts[5].x - 5, pts[5].y - 5, pts[5].x + 5, pts[5].y + 5);

		SelectObject(hdc, GetStockObject(WHITE_PEN));
		

		MoveToEx(hdc, pts[1].x, pts[1].y, NULL);
		LineTo(hdc, pts[2].x, pts[2].y);

		MoveToEx(hdc, pts[2].x, pts[2].y, NULL);
		LineTo(hdc, pts[3].x, pts[3].y);

		MoveToEx(hdc, pts[0].x, pts[0].y, NULL);
		LineTo(hdc, pts[4].x, pts[4].y);

		MoveToEx(hdc, pts[2].x, pts[2].y, NULL);
		LineTo(hdc, pts[5].x, pts[5].y);

		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

