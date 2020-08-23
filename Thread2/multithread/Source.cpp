//Headers
#include<windows.h>

//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);
DWORD WINAPI ThreadProcThree(LPVOID);
DWORD WINAPI ThreadProcFour(LPVOID);

BOOL gbDone = FALSE;
RECT gRect;


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
		TEXT("MultiThreading(4)--Payal"),
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
	static HANDLE hThreadThree = NULL;
	static HANDLE hThreadFour = NULL;
	switch (iMsg)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &gRect);
		hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hwnd, 0, NULL);
		hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);
		hThreadThree = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcThree, (LPVOID)hwnd, 0, NULL);
		hThreadFour = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcFour, (LPVOID)hwnd, 0, NULL);

		break;

	case WM_SIZE :
		GetClientRect(hwnd, &gRect);
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("This is Multithreading Application"), TEXT("message"), MB_OK);
		break;

	case WM_DESTROY:
		if (hThreadOne) {
			CloseHandle(hThreadOne);
			hThreadOne = NULL;
		}
		
		if (hThreadTwo) {
			CloseHandle(hThreadTwo);
			hThreadTwo = NULL;
		}

		if (hThreadThree) {
			CloseHandle(hThreadThree);
			hThreadThree = NULL;
		}

		if (hThreadFour) {
			CloseHandle(hThreadFour);
			hThreadFour = NULL;
		}
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID param) {

	//local variable

	HDC hdc;
	LONG i;
	TCHAR str[255];

	//code

	hdc = GetDC((HWND)param);
	for (i = 0; i < 4194303; i++) {

		SetBkColor(hdc, RGB(0, 0, 0));
		SetTextColor(hdc, RGB(255, 0, 0));
		wsprintf(str, TEXT("Thread1 : incresing order : %lu "), i);
		TextOut(hdc, 20, 10, str, wcslen(str));

		SetBkColor(hdc, RGB(0, 0, 0));
		SetTextColor(hdc, RGB(0, 255, 0));
		wsprintf(str, TEXT("Thread2 : decresing order : %lu "), 4194303-i);
		TextOut(hdc, 20, 35, str, wcslen(str));
	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}

DWORD WINAPI ThreadProcTwo(LPVOID param) {

	//local variable

	HDC hdc;
	HBRUSH hBrush;
	RECT rc;

	//code

	hdc = GetDC((HWND)param);

	while(gbDone == FALSE) {

		rc.left = gRect.right / 2 + (rand() % gRect.right / 2);	//2nd quadrant + rignt side of screen

		rc.top = gRect.top        + (rand() % gRect.bottom / 2);

		rc.right = gRect.right / 2 + (rand() % gRect.right / 2);

		rc.bottom = rand() % gRect.bottom / 2;

		hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
		FillRect(hdc, &rc, hBrush);
		DeleteObject(hBrush);
		
	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}

DWORD WINAPI ThreadProcThree(LPVOID param) {

	//local variable

	HDC hdc;
	HBRUSH hBrush;
	RECT rc;

	//code

	hdc = GetDC((HWND)param);

	while (gbDone == FALSE) {

		rc.left = gRect.right / 2 + (rand() % gRect.right / 2);	

		rc.top = gRect.bottom / 2 + (rand() % gRect.bottom / 2);

		rc.right = gRect.right / 2 + (rand() % gRect.right / 2);

		rc.bottom = gRect.bottom / 2 + (rand() % gRect.bottom / 2);

		hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
		SelectObject(hdc, hBrush);
		Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
		DeleteObject(SelectObject(hdc,GetStockObject(WHITE_BRUSH)));

	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}

DWORD WINAPI ThreadProcFour(LPVOID param) {

	//local variable

	HDC hdc;
	HBRUSH hBrush;
	RECT rc;

	//code

	hdc = GetDC((HWND)param);

	while (gbDone == FALSE) {

		rc.left = gRect.left  + (rand() % gRect.right / 2);	

		rc.top = gRect.bottom / 2 + (rand() % gRect.bottom / 2);

		rc.right = gRect.left  + (rand() % gRect.right / 2);

		rc.bottom = gRect.bottom / 2 + (rand() % gRect.bottom / 2);

		hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
		SelectObject(hdc, hBrush);
		RoundRect(hdc, rc.left, rc.top, rc.right, rc.bottom,rand()%20,rand()%20);
		DeleteObject(SelectObject(hdc, GetStockObject(WHITE_BRUSH)));

	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}