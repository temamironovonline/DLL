#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <malloc.h>
#include "HeaderDLL.h"

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
    searchSurnameIvanova(people);
}

void searchSurname(struct users* people)
{
    struct users* currentPeople = malloc(sizeof(struct users));
    struct users* forCurrentPeople;
    int j = 0, countOfRows = 1;
    char* forComprasion = "Гуськов";
    for (int i = 0; i < 100; i++)
    {
        if (strstr(people[i].surname, forComprasion) != NULL)
        {
            currentPeople[j] = people[i];
            forCurrentPeople = realloc(currentPeople, (j + 2) * sizeof(struct users));
            j++;
            currentPeople = forCurrentPeople;
        }
    }
    writeToFile(currentPeople, j);
}

void searchSurnameIvanova(struct users* people)
{
    struct users* currentPeople = malloc(sizeof(struct users));
    struct users* forCurrentPeople;
    int j = 0, countOfRows = 1;
    char* forComprasion = "Иванова";
    for (int i = 0; i < 100; i++)
    {
        if (strstr(people[i].surname, forComprasion) != NULL)
        {
            currentPeople[j] = people[i];
            forCurrentPeople = realloc(currentPeople, (j + 2) * sizeof(struct users));
            j++;
            currentPeople = forCurrentPeople;
        }
    }
    writeToFileIvanova(currentPeople, j);
}

void writeToFile(struct users* currentPeople, int countCurrentPeople)
{
    HANDLE fileResult = CreateFile(L"Result.csv", // создаваемый файл
        GENERIC_WRITE, // открывается для записи
        FILE_SHARE_WRITE, // совместно не используется
        NULL, // защита по умолчанию
        CREATE_ALWAYS, // переписывает существующий
        FILE_ATTRIBUTE_NORMAL, // асинхронный ввод/вывод I/O
        NULL); // атрибутов шаблона нет
    DWORD countFileSymbols;
    float averageAge = 0;
    char* dataForWritting = calloc(100, sizeof(char));
    for (int i = 0; i < countCurrentPeople; i++)
    {
        sprintf(dataForWritting, "%s;%s;%s;%d\n", currentPeople[i].surname, currentPeople[i].name, currentPeople[i].midname, currentPeople[i].age);
        WriteFile(fileResult, dataForWritting, strlen(dataForWritting), &countFileSymbols, NULL);
        averageAge += currentPeople[i].age;
    }
    averageAge /= countCurrentPeople;
    sprintf(dataForWritting, "Средний возраст: %f", averageAge);
    WriteFile(fileResult, dataForWritting, strlen(dataForWritting), &countFileSymbols, NULL);
    free(dataForWritting);
    CloseHandle(fileResult);
}

void writeToFileIvanova(struct users* currentPeople, int countCurrentPeople)
{
    HANDLE fileResult = CreateFile(L"ResultIvanova.csv", // создаваемый файл
        GENERIC_WRITE, // открывается для записи
        FILE_SHARE_WRITE, // совместно не используется
        NULL, // защита по умолчанию
        CREATE_ALWAYS, // переписывает существующий
        FILE_ATTRIBUTE_NORMAL, // асинхронный ввод/вывод I/O
        NULL); // атрибутов шаблона нет
    DWORD countFileSymbols;
    float averageAge = 0;
    char* dataForWritting = calloc(100, sizeof(char));
    for (int i = 0; i < countCurrentPeople; i++)
    {
        sprintf(dataForWritting, "%s;%s;%s;%d\n", currentPeople[i].surname, currentPeople[i].name, currentPeople[i].midname, currentPeople[i].age);
        WriteFile(fileResult, dataForWritting, strlen(dataForWritting), &countFileSymbols, NULL);
        averageAge += currentPeople[i].age;
    }
    averageAge /= countCurrentPeople;
    sprintf(dataForWritting, "Средний возраст: %f", averageAge);
    WriteFile(fileResult, dataForWritting, strlen(dataForWritting), &countFileSymbols, NULL);
    free(dataForWritting);
    CloseHandle(fileResult);
}