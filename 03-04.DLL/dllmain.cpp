﻿// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

void fnMy0304DLL(int** InPointer)
{
    std::cout << __func__ << std::endl;
    *InPointer = new int{ 100 };
}

void MYDLL_API fnMy0304DLLFree(int** InPointer)
{
    delete *InPointer;
    *InPointer = nullptr;
}
