#include "DeleteAccountTask.h"
#include "MISC/Utils.h"
#include "Classes/DataBase.h"

FDeleteAccountTask::FDeleteAccountTask()
{
	FAccount Account = FUtils::MakeAccountFromUserinput();
	const bool Result = GDataBase.DeleteAccount(Account);

	FUtils::PrintSystem(Result, __FUNCTION__);
}
