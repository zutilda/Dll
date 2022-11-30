#include <Windows.h>
#define PATH L"DLLCode.dll"
typedef DWORD (_cdecl* MyFunction)(DWORD*);
typedef DWORD(_cdecl* MyFunctionTreads)(DWORD*, DWORD);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int mCmdShow)
{
	HINSTANCE hMyDLL;
	if ((hMyDLL = LoadLibrary(PATH)) == NULL) return 1;
	DWORD* n = calloc(2, sizeof(DWORD));
	n[0] = 2;
	n[1] = 20;
	MyFunction myFunc = (MyFunction)GetProcAddress(hMyDLL, "Count");
	DWORD r = myFunc(n);

	MyFunctionTreads myFuncTr = (MyFunctionTreads)GetProcAddress(hMyDLL, "Threads");
	DWORD rT = myFuncTr(n, 18);
	FreeLibrary(hMyDLL);
	return 0;
}