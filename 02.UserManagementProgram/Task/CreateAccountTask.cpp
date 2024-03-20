#include "CreateAccountTask.h"
#include "MISC/Utils.h"
#include "Classes/DataBase.h"

FCreateAccountTask::FCreateAccountTask()
{
	FAccount Account = FUtils::MakeAccountFromUserinput();
	FAccount* Result = GDataBase.CreateAccount(Account);
	if (Result)
	{
		cout << format("[System]{} sucess\n", __FUNCTION__);
	}
	else
	{
		cout << format("[System]{} failed\n", __FUNCTION__);
	}
}
