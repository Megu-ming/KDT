#include "DeleteAccountTask.h"
#include "MISC/Utils.h"
#include "Classes/DataBase.h"
#include "LogoutTask.h"

FDeleteAccountTask::FDeleteAccountTask()
{
	cout << "[----- Delete Account ------]" << endl;
	const FAccount Account = FUtils::MakeAccountFromUserInput();
	if (GDataBase.CheckAccount(Account))
	{
		FLogoutTask LogoutTask(Account);
	}
	const bool Result = GDataBase.DeleteAccount(Account);

	FUtils::PrintSystem(Result, __func__);
}
