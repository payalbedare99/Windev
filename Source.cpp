//Headers
#include<windows.h>
#include"Source.h"

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
		TEXT("Payal..Bitmap"),
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
	static HBITMAP hBitmap[2];
	static BITMAP bitmap;
	static HDC hdc, hdcMem;
	static HINSTANCE hInstance;
	PAINTSTRUCT ps;
	RECT rc;
	//code
	switch (iMsg)
	{
	case WM_CREATE:

		hInstance = GetModuleHandle(NULL);
		hBitmap[0] = LoadBitmap(hInstance, MAKEINTRESOURCE(MYBITMAP1));
		hBitmap[1] = LoadBitmap(hInstance, MAKEINTRESOURCE(MYBITMAP2));

		hdcMem = CreateCompatibleDC(NULL);
		SetTimer(hwnd, 110, 1000, NULL);
		break;

	case WM_TIMER:
		KillTimer(hwnd, 110);
		iPaintFlag++;
		if (iPaintFlag > 1)
			iPaintFlag = 0;
		InvalidateRect(hwnd, NULL, TRUE);
		SetTimer(hwnd, 110, 1000, NULL);

		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdcMem, hBitmap[iPaintFlag]);
		GetObject(hBitmap[iPaintFlag], sizeof(BITMAP), &bitmap);
		StretchBlt(hdc, 0, 0, rc.right, rc.bottom, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		DeleteObject(hBitmap);
		DeleteObject(hdcMem);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}