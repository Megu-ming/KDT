#pragma once
#include "Classes/Account.h"

struct FUtils
{
	static FAccount MakeAccountFromUserinput()
	{
		FAccount Account;
		cout << " Input ID: ";
		cin >> Account.ID;

		
		cout << " Input Password: ";
		cin >> Account.Password;

		return Account;
	}

	static void PrintSystem(bool bFlag, const char* InFunctionName)
	{
		if (bFlag)
		{
			cout << format("[System]{} sucess\n", InFunctionName);
		}
		else
		{
			cout << format("[System]{} failed\n", InFunctionName);
		}
	}
};

