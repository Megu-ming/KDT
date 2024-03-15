#pragma once
#include "BaseVirtual.h"

class FDerivedVirtual : public FBaseVirtual
{
public:
	FDerivedVirtual();
	~FDerivedVirtual();

	// override : 재정의 했다고 티를 낸다.
	virtual void PublicMethod() override;

public:
	int DerivedPublicValue = 11;
	int DerivedPublicValue2 = 12;

};

