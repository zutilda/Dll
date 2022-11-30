#include <Windows.h>
#include <malloc.h>

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
extern __declspec(dllimport) DWORD Count(DWORD*);

DWORD Count(DWORD* n)
{	
	if ((n[0] > 1) && (n[1] > n[0]))
	{
		DWORD  d = 0;	
		for (n[0]; n[0] <= n[1]; n[0]++)
		{ 
			DWORD  k = 0;
			for (DWORD i = 2; i < n[0]; i++)
			{
				if (n[0] % i == 0) k++;
				else k+=0;
			}
			if (k == 0) d++;
			else d += 0;
		}
		return d;
	}
	else
		return 0;
}

extern __declspec(dllimport) DWORD Threads(DWORD*, DWORD);

DWORD Threads(DWORD* n, DWORD countTreads)
{
	if ((n[0] > 1) && (n[1] > n[0]))
	{
		DWORD diff = n[1] - n[0];

		if(diff < countTreads) return 0;

		HANDLE* threads;
		DWORD** n;
		n = calloc(2, sizeof(DWORD*));
		DWORD* n1 = n[0], n2 = n[1];

		threads = calloc(countTreads, sizeof(HANDLE));

		for (size_t i = 0; i < countTreads; i++)
		{
			*n[0] = n1;
			n1 += 1;
			*(n[1] + i) = n1;

			*(threads + i) = CreateThread(NULL, NULL, Count(*n), *(n[1] + i), NULL, NULL);
			n1++;
		}

		**(n + countTreads - 1) = n1;
		*(*(n + countTreads - 1) + 1) = n1;

		*(threads + countTreads - 1) = CreateThread(NULL, NULL, Count(*n), *(n + countTreads - 1), NULL, NULL);
		WaitForMultipleObjects(countTreads, threads, TRUE, INFINITE);

		DWORD count = 0;

		for (size_t i = 0; i < countTreads + 1; i++)
		{
			DWORD code;
			GetExitCodeThread(threads[i], &code);
			CloseHandle(threads[i]);
			count += code;
		}

		free(n);
		free(threads);

		return count;
	}
	else return 0;
}
//extern "C" __declspec(dllimport) int Hello(LPWSTR str);
//int Hello(LPWSTR str)
//{
//	MessageBox(NULL, str, L"Проверка связи", MB_OK);
//	return 0;
//}
//
//extern "C" __declspec(dllimport) int Sum(int a, int b);
//int Sum(int a, int b)
//{
//	return a + b;
//}