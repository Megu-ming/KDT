#include "DeleteAccountTask.h"
#include "MISC/Utils.h"
#include "Classes/DataBase.h"

FDeleteAccountTask::FDeleteAccountTask()
{
	FAccount Account = FUtils::MakeAccountFromUserinput();
	const bool Result = GDataBase.DeleteAccount(Account);

	if (Result)
	{
		cout << format("[System]{} sucess\n", __FUNCTION__);
	}
	else
	{
		cout << format("[System]{} failed\n", __FUNCTION__);
	}
}
