#include "Derived.h"

FDerived::FDerived()
	// FDerived의 초기화 구문에서는 부모 변수에 접근할 수 없습니다.
	// : ProtectedValue(100)
	: DerivedPublicValue(11)
	, DerivedPublicValue2(12)
{
	this->DerivedPublicValue;
	this->DerivedPublicValue2;
	this->ProtectedValue;	// 부모의 protected 변수에 접근 가능
	this->PublicValue;
	// this->PublicMethod();
	std::cout << __FUNCTION__ << std::endl;
}

FDerived::~FDerived()
{
	std::cout << __FUNCTION__ << std::endl;
}

void FDerived::PublicMethod()
{
	std::cout << __FUNCTION__ << std::endl;
}
