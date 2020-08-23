//Headers
#include<windows.h>
#include<stdio.h>
#include"Source.h"
#define MYTIMER1 600
#define MYTIMER2 800

//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int flag = -2;

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
		TEXT("Payal..Pledge"),
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

TCHAR word[100];
TCHAR* wptr = NULL;
int index = 0;
int wIndex = 0;
int cnt = -2;
char pledge[13][50] = {
	{"India is my country ."},
	{"All Indians are my brothers and sisters ."},
	{"I love my country ."},
	{"I am proud of its rich and varied heritage ."},
	{"I shall strive to be worthy of it ."},
	{"I shall respect my parents, ."},
	{"teachers and all elders ."},
	{"and treat everyone with courtesy ."},
	{"To my country and all my people ."},
	{"I pledge my devotion ."},
	{"In their well being ."},
	{"and prosperity alone, lies my happiness ." },
	{"Jay Hind ."}

};

int i = -2;
int row = 0;
TCHAR ch[10];
int l, r;
HFONT hFont;
int itr = 0;
TCHAR* curWord = NULL;
int yinc = 50;
SIZE strSize;
int xStart, yStart;


void getWord(int cnt) {

	while (pledge[cnt][itr] != '.') {

		word[wIndex++] = pledge[cnt][itr++];
	}
	word[wIndex] = '\0';
	wIndex = 0;
	itr = 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc;
	static HINSTANCE hInstance;
	PAINTSTRUCT ps;
	RECT rc;
	//code
	switch (iMsg)
	{
	case WM_CREATE:

		hInstance = GetModuleHandle(NULL);

		hFont = CreateFont(50, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Cambria"));
		SetTimer(hwnd, MYTIMER1, MYTIMER2, NULL);
		break;

	case WM_TIMER :
		KillTimer(hwnd, MYTIMER1);

		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_KEYDOWN:
		SetTimer(hwnd, MYTIMER1, MYTIMER2, NULL);
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		getWord(cnt++);
		
		GetTextExtentPoint32(hdc,word,wcslen(word),&strSize);

		xStart = (rc.right / 2) - strSize.cx;
		yStart = yStart + 50;
		SelectObject(hdc, hFont);
		SetBkColor(hdc, RGB(0, 0, 0));

		if (cnt < 4) {
			SetTextColor(hdc, RGB(255, 153, 51));
		}
		else if (cnt < 6) {
			SetTextColor(hdc, RGB(255, 255, 255));
		}
		else if (cnt < 8) {
			SetTextColor(hdc, RGB(0, 0, 128));
		}
		else if (cnt < 10) {
			SetTextColor(hdc, RGB(255, 255, 255));
		}
		else {
			SetTextColor(hdc, RGB(19, 136, 8));
		}
	wsprintf(ch, TEXT("%S"), word);
		TextOut(hdc, xStart, yStart, word, wcslen(word));

		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		DeleteObject(hFont);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}