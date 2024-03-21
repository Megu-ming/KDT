#include "DeleteAccountTask.h"
#include "MISC/Utils.h"
#include "Classes/DataBase.h"

FDeleteAccountTask::FDeleteAccountTask()
{
	cout << "[----- Delete Account ------]" << endl;
	FAccount Account = FUtils::MakeAccountFromUserInput();
	const bool Result = GDataBase.DeleteAccount(Account);

	FUtils::PrintSystem(Result, __func__);
}