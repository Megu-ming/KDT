#include "LogoutTask.h"
#include "Classes/LoginSession.h"
#include "MISC/Utils.h"

FLogoutTask::FLogoutTask()
{
	cout << "[--------- Logout ----------]" << endl;
	const FAccount Account = FUtils::MakeAccountFromUserInput();
	pair Result = GLoginSession.LogOut(Account);
	cout << Result.second << endl;
}

FLogoutTask::FLogoutTask(const FAccount& InAccount)
{
	ExecuteTask(InAccount);
}

void FLogoutTask::ExecuteTask(const FAccount& InAccount)
{
	pair Result = GLoginSession.LogOut(InAccount);
	cout << Result.second << endl;
}
