#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <malloc.h>
#include "HeaderDLL.h"
#include <time.h>

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpvReserved)  // reserved
{
    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // Initialize once for each new process.
        // Return FALSE to fail DLL load.
        break;

    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;

    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:

        // Perform any necessary cleanup.
        break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}


HANDLE* forThread = NULL;
int countThreads = 0;
int count = 0;
int* answer = 0;
CRITICAL_SECTION section = { 0 };

__declspec(dllimport) int simpleDigit(int* forArg);
__declspec(dllimport) int simpleDigitThreads(int* forArg, int count);

int simpleDigit(int* forArg)
{
    answer = calloc(2, sizeof(int));
    InitializeCriticalSection(&section);

    int check = 0;
    if (forArg[0] == 1) forArg[0]++;
    EnterCriticalSection(&section);
    count = 0;
    
    for (int i = forArg[0]; i <= forArg[1]; i++)
    {
        for (int j = 2; j <= forArg[1]; j++)
        {
            if ((i % j == 0) && (i != j))
            {
                check = 1;
                break;
            }
        }
        if (check == 0)
        {
            count++;
        }
        else
        {
            check = 0;
        }
    }
    LeaveCriticalSection(&section);
    DeleteCriticalSection(&section);
    if (forThread != NULL)
    {
        for (int i = 0; i < countThreads; i++)
        {
            ExitThread(0);
        }
    }
    else
    {   
        answer[0] = count;
        answer[1] = clock();
        return answer;
    }

}

int simpleDigitThreads(int* arguments, int countThread)
{
    forThread = calloc(sizeof(HANDLE), countThread);
    countThreads = countThread;
    DWORD dwThreadID;
    InitializeCriticalSection(&section);
    for (int i = 0; i < countThread; i++)
    {
        forThread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)simpleDigit, arguments, 0, &dwThreadID);
    }
    WaitForMultipleObjects(1, forThread, TRUE, INFINITE);
    
    answer[0] = count;
    answer[1] = clock();

    return answer;
}


