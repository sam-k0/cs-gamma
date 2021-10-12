// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "pch.h"
#include <stdio.h>
#include <fstream>
#define gmx extern "C" __declspec(dllexport)


const int EVENT_OTHER_SOCIAL = 70;

// defines function pointers for the DS map creation
void (*CreateAsynEventWithDSMap)(int, int) = NULL;
int (*CreateDsMap)(int _num, ...) = NULL;
bool (*DsMapAddDouble)(int _index, char* _pKey, double value) = NULL;
bool (*DsMapAddString)(int _index, char* _pKey, char* pVal) = NULL;


// Reg cb
gmx void RegisterCallbacks(char* arg1, char* arg2, char* arg3, char* arg4) {
    void (*CreateAsynEventWithDSMapPtr)(int, int) = (void (*)(int, int))(arg1);
    int(*CreateDsMapPtr)(int _num, ...) = (int(*)(int _num, ...)) (arg2);
    CreateAsynEventWithDSMap = CreateAsynEventWithDSMapPtr;
    CreateDsMap = CreateDsMapPtr;

    bool (*DsMapAddDoublePtr)(int _index, char* _pKey, double value) = (bool(*)(int, char*, double))(arg3);
    bool (*DsMapAddStringPtr)(int _index, char* _pKey, char* pVal) = (bool(*)(int, char*, char*))(arg4);

    DsMapAddDouble = DsMapAddDoublePtr;
    DsMapAddString = DsMapAddStringPtr;
}

gmx double gmDsMapAddDouble(double map, const char* key, double value)
{
    map = (int)map;
    {
        printf("[extension] DSMAP found! Adding values: %s and %d \n", key, int(value));
        DsMapAddDouble(map, _strdup(key), int(value));
        return (double)map;
    }
}

gmx double gmDsMapAddString(double map, const char* key, const char* value)
{
    map = (int)map;
    {
        printf("[extension] DSMAP found! Adding values: %s and %s \n", key, value);
        DsMapAddString(map, _strdup(key), _strdup(value));
        return (double)map;
    }
}

gmx double gmDsMapCreate()
{
    int map = CreateDsMap(0);
    return (double) map;
}

gmx double gmCopyFile(const char* origin, const char* target)
{
    std::ifstream originfile; 
    std::ofstream targetfile;
    printf("[extension] Open files...\n");

    originfile.open(origin);
    targetfile.open(target);

    printf("[extension] Reading files...\n");
    targetfile << originfile.rdbuf();

    printf("[extension] Closing files...\n");
    originfile.close();
    targetfile.close();

    printf("[extension] Done!\n");
    return double(1);
}



// Callback?
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        //printf("[extension] DLL attached to process. \n");
    case DLL_THREAD_ATTACH:
        //printf("[extension] DLL attached to thread. \n");
    case DLL_THREAD_DETACH:
        //printf("[extension] DLL detached from thread. \n");
    case DLL_PROCESS_DETACH:
        //printf("[extension] DLL detached from process. \n");
        break;
    }
    return TRUE;
}

