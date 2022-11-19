#include <Windows.h>
#include <stdio.h>
#include "HeaderEXE.h"
#define PATH L"DLL.dll"

typedef int(_cdecl* forFirstFunction)(int firstDigit, int secondDigit);

int main(void)
{
	HINSTANCE hMyDLL;
	if ((hMyDLL = LoadLibrary(PATH)) == NULL) return 1;
	forFirstFunction myFun = (forFirstFunction)GetProcAddress(hMyDLL, "simpleDigit");
	
	printf("¬ведите начало диапазона: ");
	int first;
	scanf_s("%d", &first);

	printf("¬ведите конец диапазона: ");
	int second;
	scanf_s("%d", &second);

	int answer;
	answer = myFun(first, second);

	printf("%d", answer);
	FreeLibrary(hMyDLL);
	return 0;
}