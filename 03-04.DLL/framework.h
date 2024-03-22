#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#ifdef MY_DLL
#define MYDLL_API __declspec(dllexport) // 내보낼 dll에서 사용하는 키워드
#else
#define MYDLL_API __declspec(dllimport) // 사용할 소스코드에서 사용하는 키워드
#endif

void MYDLL_API fnMy0304DLL(int** InPointer);
void MYDLL_API fnMy0304DLLFree(int** InPointer);

class FClass
{
public:
	void MYDLL_API Test2();
};