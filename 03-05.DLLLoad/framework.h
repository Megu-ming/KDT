#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <iostream>
#ifdef MY_DLLLOAD
#define MYDLLLOAD_API __declspec(dllexport) // 내보낼 dll에서 사용하는 키워드
#else
#define MYDLLLOAD_API __declspec(dllimport) // 사용할 소스코드에서 사용하는 키워드
#endif


// 맹글링을 하지 않겠다.
extern "C"
{
	void MYDLLLOAD_API fnMy0305DLL(int** InPointer);
	void MYDLLLOAD_API fnMy0305DLLFree(int** InPointer);
}