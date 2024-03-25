#include "pch.h"

void MYDLLLOAD_API fnMy0305DLL(int** InPointer)
{
    std::cout << __func__ << std::endl;
    *InPointer = new int{ 100 };
}

void MYDLLLOAD_API fnMy0305DLLFree(int** InPointer)
{
    delete* InPointer;
    *InPointer = nullptr;
}
