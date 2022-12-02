#include <Windows.h>
#include <stdio.h>
#include <malloc.h>
#define PATH L"DLLCode.dll"
typedef int (_cdecl* MyFunction)(int*);
typedef int(_cdecl* MyFunctionTreads)(int*, int);

int main(void)
{
	system("chcp 1251>nul");
	HINSTANCE hMyDLL;
	if ((hMyDLL = LoadLibrary(PATH)) == NULL) return 1;
	int* n = calloc(2, sizeof(int));
	n[0] = 2;
	n[1] = 20;
	MyFunction myFunc = (MyFunction)GetProcAddress(hMyDLL, "Count");
	int* r = calloc(2, sizeof(int));
	r = myFunc(n);
	for (int i = 0; i < 2; i++)
	{
		printf("%d\n", r[i]);
	}

	MyFunctionTreads myFuncTr = (MyFunctionTreads)GetProcAddress(hMyDLL, "Threads");
	int* rT = calloc(2, sizeof(int));
	rT=	myFuncTr(n, 6);
	for (int i = 0; i < 2; i++)
	{
		printf("%d\n", rT[i]);
	}
	FreeLibrary(hMyDLL);
	return 0;
}