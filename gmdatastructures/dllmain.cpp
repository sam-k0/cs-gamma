// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "pch.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <cstdarg>
#include <vector>
#include <string>
#define gmx extern "C" __declspec(dllexport)


const int EVENT_OTHER_SOCIAL = 70;

// defines function pointers for the DS map creation
void (*CreateAsynEventWithDSMap)(int, int) = NULL;
int (*CreateDsMap)(int _num, ...) = NULL;
bool (*DsMapAddDouble)(int _index, char* _pKey, double value) = NULL;
bool (*DsMapAddString)(int _index, char* _pKey, char* pVal) = NULL;


// Reg cb - Do not touch
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

gmx double cs_map_create() // Create a dsmap
{
    int map = CreateDsMap(0);
    std::cout << "[extension] Creating DSMAP!\n";
    return (double)map;
}

gmx double cs_map_add_double(double map, const char* key, double value) // Adds a double value to the dsmap
{
    map = (int)map;
    {
        printf("[extension] DSMAP found! Adding values: %s and %d \n", key, int(value));
        DsMapAddDouble(map, _strdup(key), (value));
        return (double)map;
    }
}

gmx double cs_map_add_string(double map, const char* key, const char* value) // Adds a string value to the dsmap
{
    map = (int)map;
    {
        printf("[extension] DSMAP found! Adding values: %s and %s \n", key, value);
        DsMapAddString(map, _strdup(key), _strdup(value));
        return (double)map;
    }
}

gmx double cs_map_add_map(double map, const char* key, double valmap) // add a dsmap to a dsmap
{
    map = (int)map;
    valmap = (int)valmap;
    {
        printf("[extension] DSMAP found! Adding values: %s and dsmap %d \n", key, (int)valmap);
        DsMapAddDouble(map, _strdup(key), int(valmap));
        return (double)map;
    }
}

// Add 1 or more values to a dsmap (Can only allocate to numeric keys)
gmx double cs_map_add_multiple(double map, double startkey, double count, double val1, double val2, double val3, double val4, double val5 ) 
{
    map = int(map);
    startkey = int(startkey);

    std::vector<double> *args = new std::vector<double> ; // Vector holding the values
    // Add all elements to the vec
    args->push_back(val1);
    args->push_back(val2);
    args->push_back(val3);
    args->push_back(val4);
    args->push_back(val5);
    // Now iterate over 0 -> count entries
    if (count > 5) // Keep count in bounds
    {
        count = 5;
    }

    for (int i = 0; i < (int)count; i++)
    {
        // Add to dsmap
        DsMapAddDouble(map, &(std::to_string(int(startkey)))[0], args->at(i));
        std::cout << "Added value " << args->at(i) << " to DSMAP!" << std::endl;
        startkey++;
    }

    return double(1);
}


// Misc
gmx double cs_copy_file_text(const char* origin, const char* target)
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

