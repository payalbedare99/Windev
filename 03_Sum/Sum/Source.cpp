//Headers
#include<windows.h>

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
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//register above class
	RegisterClassEx(&wndclass);

	MessageBox(NULL, TEXT("Message Before CreateWindow "), TEXT(""), MB_OK);
	//create window
	hwnd = CreateWindow(szAppName,
		TEXT("Payal..Sum using wsprintf"),
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		400,
		400,
		NULL,
		NULL,
		hInstance,
		NULL);

	MessageBox(hwnd, TEXT("Message After CreateWindow "), TEXT(""), MB_OK);

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
	static int a = 20, b = 25, c;
	TCHAR str[255];
	static int x, y, w, h;
	static char ch;
	//code
	switch (iMsg)
	{
	case WM_CREATE:
		//wsprintf(str,TEXT("wParam : %d lParan : %d"),wParam,lParam);

		x = ((LPCREATESTRUCT)lParam)->x;
		y = ((LPCREATESTRUCT)lParam)->y;
		w = ((LPCREATESTRUCT)lParam)->cx;
		h = ((LPCREATESTRUCT)lParam)->cy;

		c = a + b;
	
		break;
	
	case WM_LBUTTONDOWN :

		//wsprintf(str, TEXT("Co-ordinates of Mouse (x,y) : %d   %d"), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		wsprintf(str, TEXT("Key Pressed in WM_KeyDown : %c"), ch);
		MessageBox(hwnd, str , TEXT("WM_KEYDOWN output"), MB_OK);

		break;

	case WM_RBUTTONDOWN:

		//	wsprintf(str, TEXT("Co-ordinates of Mouse (x,y) : %d   %d"), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		wsprintf(str, TEXT("x = %d y = %d w = %d h = %d "), x,y,w,h);
		MessageBox(hwnd, str, TEXT("From lParam of WM_CREATE..."), MB_OK);

		wsprintf(str, TEXT("The sum of %d and %d is %d "), a,b,c);
		MessageBox(hwnd, str, TEXT("Sum.."), MB_OK);

		break;

	case WM_KEYDOWN :
		ch = wParam;
		wsprintf(str, TEXT("Key Pressed = %c"), wParam);
		MessageBox(hwnd, str, TEXT("Key Found"), MB_OK);
		break;

	case WM_DESTROY:
		MessageBox(hwnd, TEXT("wm_destroy is received"), TEXT("MSG"), MB_OK);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}