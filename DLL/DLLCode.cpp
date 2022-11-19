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



__declspec(dllimport) int simpleDigit(int forStart, int forEnd);

int simpleDigit(int forStart, int forEnd)
{
    int count = 0;
    int check = 0;
    for (int i = forStart; i <= forEnd; i++)
    {
        for (int j = 2; j <= forEnd; j++)
        {
            if (i % j == 0 && i != j)
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
    return count-1;
}

int simpleDigitThreads(int forStart, int forEnd, int countThread)
{
    HANDLE* forThread = calloc(sizeof(HANDLE), countThread);
    int* digits = calloc

    for (int i = 0; i < countThread; i++)
    {
        forThread[i] = CreateThread(NULL, 0, simpleDigit, timeArray, 0, 0); // Поток с подсчетом времени
    }
}



//
//void searchSurname(struct users* people)
//{
//    struct users* currentPeople = malloc(sizeof(struct users));
//    struct users* forCurrentPeople;
//    int j = 0, countOfRows = 1;
//    char* forComprasion = "Гуськов";
//    for (int i = 0; i < 100; i++)
//    {
//        if (strstr(people[i].surname, forComprasion) != NULL)
//        {
//            currentPeople[j] = people[i];
//            forCurrentPeople = realloc(currentPeople, (j + 2) * sizeof(struct users));
//            j++;
//            currentPeople = forCurrentPeople;
//        }
//    }
//    writeToFile(currentPeople, j);
//}
//
//void searchSurnameIvanova(struct users* people)
//{
//    struct users* currentPeople = malloc(sizeof(struct users));
//    struct users* forCurrentPeople;
//    int j = 0, countOfRows = 1;
//    char* forComprasion = "Иванова";
//    for (int i = 0; i < 100; i++)
//    {
//        if (strstr(people[i].surname, forComprasion) != NULL)
//        {
//            currentPeople[j] = people[i];
//            forCurrentPeople = realloc(currentPeople, (j + 2) * sizeof(struct users));
//            j++;
//            currentPeople = forCurrentPeople;
//        }
//    }
//    writeToFileIvanova(currentPeople, j);
//}
//
//void writeToFile(struct users* currentPeople, int countCurrentPeople)
//{
//    HANDLE fileResult = CreateFile(L"Result.csv", // создаваемый файл
//        GENERIC_WRITE, // открывается для записи
//        FILE_SHARE_WRITE, // совместно не используется
//        NULL, // защита по умолчанию
//        CREATE_ALWAYS, // переписывает существующий
//        FILE_ATTRIBUTE_NORMAL, // асинхронный ввод/вывод I/O
//        NULL); // атрибутов шаблона нет
//    DWORD countFileSymbols;
//    float averageAge = 0;
//    char* dataForWritting = calloc(100, sizeof(char));
//    for (int i = 0; i < countCurrentPeople; i++)
//    {
//        sprintf(dataForWritting, "%s;%s;%s;%d\n", currentPeople[i].surname, currentPeople[i].name, currentPeople[i].midname, currentPeople[i].age);
//        WriteFile(fileResult, dataForWritting, strlen(dataForWritting), &countFileSymbols, NULL);
//        averageAge += currentPeople[i].age;
//    }
//    averageAge /= countCurrentPeople;
//    sprintf(dataForWritting, "Средний возраст: %f", averageAge);
//    WriteFile(fileResult, dataForWritting, strlen(dataForWritting), &countFileSymbols, NULL);
//    free(dataForWritting);
//    CloseHandle(fileResult);
//}
//
//void writeToFileIvanova(struct users* currentPeople, int countCurrentPeople)
//{
//    HANDLE fileResult = CreateFile(L"ResultIvanova.csv", // создаваемый файл
//        GENERIC_WRITE, // открывается для записи
//        FILE_SHARE_WRITE, // совместно не используется
//        NULL, // защита по умолчанию
//        CREATE_ALWAYS, // переписывает существующий
//        FILE_ATTRIBUTE_NORMAL, // асинхронный ввод/вывод I/O
//        NULL); // атрибутов шаблона нет
//    DWORD countFileSymbols;
//    float averageAge = 0;
//    char* dataForWritting = calloc(100, sizeof(char));
//    for (int i = 0; i < countCurrentPeople; i++)
//    {
//        sprintf(dataForWritting, "%s;%s;%s;%d\n", currentPeople[i].surname, currentPeople[i].name, currentPeople[i].midname, currentPeople[i].age);
//        WriteFile(fileResult, dataForWritting, strlen(dataForWritting), &countFileSymbols, NULL);
//        averageAge += currentPeople[i].age;
//    }
//    averageAge /= countCurrentPeople;
//    sprintf(dataForWritting, "Средний возраст: %f", averageAge);
//    WriteFile(fileResult, dataForWritting, strlen(dataForWritting), &countFileSymbols, NULL);
//    free(dataForWritting);
//    CloseHandle(fileResult);
//}