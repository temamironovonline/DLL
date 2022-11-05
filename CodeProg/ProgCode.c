#include <Windows.h>
#include <stdio.h>
#include "HeaderEXE.h"
#define PATH L"DLL.dll"



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	HINSTANCE hMyDLL;
	if ((hMyDLL = LoadLibrary(PATH)) == NULL) return 1;
	forReadData myFun = (forReadData)GetProcAddress(hMyDLL, "readData");
	struct users* user = calloc(5000, sizeof(struct users));
	myFun(user);
	FreeLibrary(hMyDLL);
	return 0;
}