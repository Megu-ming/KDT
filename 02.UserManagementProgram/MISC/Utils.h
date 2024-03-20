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
};

