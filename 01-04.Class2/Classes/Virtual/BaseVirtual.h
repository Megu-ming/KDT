#pragma once
#include "MISC/Headers.h"

// 부모에 virtual이 하나라도 있으면
// Virtual Table을 가리키는 주소가 인스턴스를 선언할 때
// 변수 최상단에 생성된다
class FBaseVirtual
{
public:
	FBaseVirtual();
	virtual ~FBaseVirtual();

	// 멤버 함수에 virtual을 붙혔다는 것은
	// 내가 만든 함수를 재정의(override)
	// 해서 사용하는 경우
	// 너가 만든 함수를 호출해줄게 라는 뜻
	virtual void PublicMethod();

public:
	int PublicValue = 0;

protected:
	int ProtectedValue = 1;

private:
	int PrivateValue = 2;
	int PrivateValue2 = 3;
};

