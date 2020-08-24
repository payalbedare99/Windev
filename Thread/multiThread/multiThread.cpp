//Headers
#include<windows.h>

//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);
//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyWindow");

	//code
	//initialization of WINDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//register above class
	RegisterClassEx(&wndclass);

	//create window
	hwnd = CreateWindow(szAppName,
		TEXT("MultiThreading"),
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
	//code
	static HANDLE hThreadOne = NULL;
	static HANDLE hThreadTwo = NULL;
	switch (iMsg)
	{
	case WM_CREATE:
		hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hwnd, 0, NULL);
		hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("This is Multithreading Application"), TEXT("message"), MB_OK);
		break;
	case WM_DESTROY:
		CloseHandle(hThreadOne);
		CloseHandle(hThreadTwo);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID param) {

	//local variable

	HDC hdc;
	int i;
	TCHAR str[255];

	//code

	hdc = GetDC((HWND)param);
	for (i = 0; i < 65535; i++) {

		SetBkColor(hdc, RGB(0, 0, 0));
		SetTextColor(hdc, RGB(255,0,0));
		wsprintf(str, TEXT("Thread1 : incresing order : %d "), i);
		TextOut(hdc, 250, 200, str, wcslen(str));
	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}

DWORD WINAPI ThreadProcTwo(LPVOID param) {

	//local variable

	HDC hdc;
	int i;
	TCHAR str[255];

	//code

	hdc = GetDC((HWND)param);
	for (i = 65535; i >= 0; i--) {

		SetBkColor(hdc,RGB(0,0,0));
		SetTextColor(hdc,RGB(0, 255, 0));
		wsprintf(str, TEXT("Thread2 : decresing order : %d "), i);
		TextOut(hdc, 250, 400, str, wcslen(str));
	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}