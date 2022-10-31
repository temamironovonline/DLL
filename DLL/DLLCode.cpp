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
    fileStart = CreateFile(L"C:\\Users\\�����������\\source\\repos\\DLL\\DLL\\Users.csv", // ����������� ����
        GENERIC_READ, // ��������� ��� ������
        FILE_SHARE_READ, // ��� ����������� ������
        NULL, // ������ �� ���������
        OPEN_EXISTING, // ������ ������������ ����
        FILE_ATTRIBUTE_NORMAL, // ������� ����
        NULL); // ��������� ������� ���

    if (fileStart == INVALID_HANDLE_VALUE)
    {
        MessageBox(NULL, L"��� �������� ����� �������� ������!", L"���� ���������", MB_OK);
        return 0;
    }

    DWORD countFileSymbols;
    LPCSTR argumentsFromFile = calloc(3099, sizeof(CHAR));
    if (!ReadFile(fileStart, argumentsFromFile, 3099, &countFileSymbols, NULL))
    {
        MessageBox(NULL, L"��� ������ ������ �� ����� �������� ������!", L"���� ���������", MB_OK);
        return 0;
    }
    
    char* dataConvertToStruct = strtok(argumentsFromFile, ";");
    int countRecords;

    for (int i = 0; i<100; i++)
    {
        countRecords = i;
        people[i].surname = dataConvertToStruct;
        dataConvertToStruct = strtok(NULL, ";\r\n");

        people[i].name = dataConvertToStruct;
        dataConvertToStruct = strtok(NULL, ";\r\n");

        people[i].midname = dataConvertToStruct;
        dataConvertToStruct = strtok(NULL, ";\r\n");

        people[i].age = atoi(dataConvertToStruct);
        dataConvertToStruct = strtok(NULL, ";\r\n");
        
    }
    CloseHandle(fileStart);

    searchSurname(people);
}

void searchSurname(struct users* people)
{
    struct users* currentPeople = malloc(sizeof(struct users));
    struct users* forCurrentPeople;
    int j = 0;
    char* des = "��������";
    for (int i = 0; i < 100; i++)
    {
        if (strstr(people[i].surname, des) != NULL)
        {
            currentPeople[j] = people[i];
            forCurrentPeople = realloc(currentPeople, (j + 2) * sizeof(struct users));
            j++;
            currentPeople = forCurrentPeople;
        }
    }
    
    MessageBox(NULL, L"awd", L"Wassup", MB_OK);
}

void writeToFile(struct users* currentPeople)
{
    HANDLE fileResult = CreateFile(L"Result.txt", // ����������� ����
        GENERIC_WRITE, // ����������� ��� ������
        FILE_SHARE_WRITE, // ��������� �� ������������
        NULL, // ������ �� ���������
        CREATE_ALWAYS, // ������������ ������������
        FILE_ATTRIBUTE_NORMAL, // ����������� ����/����� I/O
        NULL); // ��������� ������� ���
    DWORD countFileSymbols;
    WriteFile(fileResult, forAnswer, forCountSymbols, &countFileSymbols, NULL);
    CloseHandle(fileResult);
}