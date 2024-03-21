#include "LoginTask.h"
#include "Classes/LoginSession.h"
#include "MISC/Utils.h"
#include "Classes/DataBase.h"

FLoginTask::FLoginTask()
{
	cout << "[---------- Login ----------]" << endl;
	FAccount Account = FUtils::MakeAccountFromUserInput();
	pair Result = GLoginSession.Login(Account);
	cout << Result.second << endl;
}
