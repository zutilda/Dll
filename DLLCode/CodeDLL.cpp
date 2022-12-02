#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <malloc.h>
#include <time.h>

BOOL WINAPI DllMain(HINSTANCE hlnstDll, DWORD dwReason, LPVOID IpReserved)
{
	BOOL bAllWentWell = TRUE;
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	if (bAllWentWell)
		return TRUE;
	else
		return FALSE;
}

HANDLE* threads = NULL;
int d = 0;
int* arr = 0;
int countThread = 0;
CRITICAL_SECTION section = { 0 };

extern __declspec(dllimport) int Count(int*);

int Count(int* n)
{	
	InitializeCriticalSection(&section);
	EnterCriticalSection(&section);
	if ((n[0] > 1) && (n[1] > n[0]))
	{
		arr = calloc(2, sizeof(int));
		
		for (n[0]; n[0] <= n[1]; n[0]++)
		{ 
			int  k = 0;
			for (int i = 2; i < n[0]; i++)
			{
				if (n[0] % i == 0) k++;
				else k+=0;
			}
			if (k == 0) d++;
			else d += 0;
		}
		LeaveCriticalSection(&section);
		DeleteCriticalSection(&section);
		if (threads != NULL)
		{
			for (int i = 0; i < countThread; i++)
			{
				ExitThread(0);
			}
		}
		else
		{
			arr[0] = d;
			arr[1] = clock();
			return arr;
		}
	}
	else
		return 0;
}

extern __declspec(dllimport) int Threads(int*, int);

int Threads(int* n, int countTreads)
{
	
		threads = calloc(sizeof(HANDLE), countTreads);
		countThread = countTreads;
		DWORD Thread;
		InitializeCriticalSection(&section);
		for (int i = 0; i < countThread; i++)
		{
			threads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Count, n, 0, &Thread);
		}
		WaitForMultipleObjects(1, threads, TRUE, INFINITE);

		arr[0] = d;
		arr[1] = clock();

		return arr;
	

}
