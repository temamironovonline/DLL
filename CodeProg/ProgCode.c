#include <Windows.h>
#include <stdio.h>
#include "HeaderEXE.h"
#define PATH L"DLL.dll"

typedef int(_cdecl* forFirstFunction)(int* arg);
typedef int(_cdecl* forSecondFunction)(int* arg, int count);

int main(void)
{
	system("chcp 1251");
	HINSTANCE hMyDLL;
	if ((hMyDLL = LoadLibrary(PATH)) == NULL) return 1;
	forFirstFunction myFunFirst = (forFirstFunction)GetProcAddress(hMyDLL, "simpleDigit");
	forSecondFunction myFunSecond = (forSecondFunction)GetProcAddress(hMyDLL, "simpleDigitThreads");
	
	int* arg = calloc(2, sizeof(int));

	int a = 0, b = 0;

	printf("¬ведите начало диапазона: ");
	scanf_s("%d", &a);
	arg[0] = a;

	printf("¬ведите конец диапазона: ");
	scanf_s("%d", &b);
	arg[1] = b;
	int* answer = calloc(2, sizeof(int));
	answer = myFunFirst(arg);
	for (int i = 0; i < 2; i++)
	{
		printf("%d\n", answer[i]);
	}
	answer = myFunSecond(arg, 10);

	for (int i = 0; i < 2; i++)
	{
		printf("%d\n", answer[i]);
	}
	
	
	FreeLibrary(hMyDLL);
	return 0;
}