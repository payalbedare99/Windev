#include<Windows.h>
#include"MyMath.h"
//entry point function
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved){
	//code
	switch (dwReason) {
	case DLL_PROCESS_ATTACH :		//dll Injection
		break;
	case DLL_THREAD_ATTACH :
		break;
	case DLL_THREAD_DETACH :
		break;
	case DLL_PROCESS_DETACH :
		break;
	default :
		break;
	}
	return(TRUE);
}

//exported function definition
 __declspec(dllexport) int MakeSquare(int num) {
	//code
	return num * num;
}

