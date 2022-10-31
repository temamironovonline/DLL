#include <Windows.h>
#include <stdio.h>

#define PATH L"DLL.dll"
typedef int(_cdecl* MyFunction)(LPWSTR);
typedef int(_cdecl* forReadData)(struct users*);
//typedef void(_cdecl* forReadData)();

struct users
{
	char* surname;
	char* name;
	char* midname;
	int age;
};

void check(struct users a) {

}

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