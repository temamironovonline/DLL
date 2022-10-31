#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <malloc.h>

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

__declspec(dllimport) int myFunc(LPWSTR str);
__declspec(dllimport) void readData(struct users* people);
__declspec(dllimport) void searchSurname(struct users* people);


struct users
{
    char* surname;
    char* name;
    char* midname;
    int age;
};

int myFunc(LPWSTR str)
{
    MessageBox(NULL, str, L"Wassup", MB_OK);
    return 0;
}
void readData(struct users* people)
{
    HANDLE fileStart;
    fileStart = CreateFile(L"C:\\Users\\aserg\\source\\repos\\DLL\\DLL\\Users.csv", // открываемый файл
        GENERIC_READ, // открываем для чтения
        FILE_SHARE_READ, // для совместного чтения
        NULL, // защита по умолчанию
        OPEN_EXISTING, // только существующий файл
        FILE_ATTRIBUTE_NORMAL, // обычный файл
        NULL); // атрибутов шаблона нет

    if (fileStart == INVALID_HANDLE_VALUE)
    {
        MessageBox(NULL, L"При открытии файла возникла ошибка!", L"Окно программы", MB_OK);
        return 0;
    }

    DWORD countFileSymbols;
    LPCSTR argumentsFromFile = calloc(3099, sizeof(CHAR));
    if (!ReadFile(fileStart, argumentsFromFile, 3099, &countFileSymbols, NULL))
    {
        MessageBox(NULL, L"При чтении данных из файла возникла ошибка!", L"Окно программы", MB_OK);
        return 0;
    }
    
    char* dataConvertToStruct = strtok(argumentsFromFile, ";");
    int countRecords;
    char* surname = calloc(100, sizeof(char));
    char* name = calloc(100, sizeof(char));
    char* midname = calloc(100, sizeof(char));
    for (int i = 0; i<100; i++)
    {
        countRecords = i;
        sprintf(surname, L"%s", dataConvertToStruct);
        people[i].surname = surname;
        dataConvertToStruct = strtok(NULL, ";\r\n");

        sprintf(name, L"%s", dataConvertToStruct);
        people[i].name = name;
        dataConvertToStruct = strtok(NULL, ";\r\n");

        sprintf(midname, L"%s", dataConvertToStruct);
        people[i].midname = midname;
        dataConvertToStruct = strtok(NULL, ";\r\n");

        people[i].age = atoi(dataConvertToStruct);
        dataConvertToStruct = strtok(NULL, ";\r\n");
        
    }
    CloseHandle(fileStart);

    searchSurname(people);
}

void searchSurname(struct users* people)
{
    int* indexes = calloc(1, sizeof(int));
    int j = 0;
    char* des = L"Десятков";
    people[1].surname = L"Десятков";
    for (int i = 0; i < 100; i++)
    {
        if (people[i].surname == des)
        {
            indexes[j] = i;
            indexes = realloc(j + 2, sizeof(int));
            j++;
        }
    }
    MessageBox(NULL, L"awd", L"Wassup", MB_OK);
}