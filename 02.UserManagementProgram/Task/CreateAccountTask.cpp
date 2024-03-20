#include "CreateAccountTask.h"
#include "MISC/Utils.h"
#include "Classes/DataBase.h"

FCreateAccountTask::FCreateAccountTask()
{
	FAccount Account = FUtils::MakeAccountFromUserinput();
	FAccount* Result = GDataBase.CreateAccount(Account);
	
	FUtils::PrintSystem(Result, __FUNCTION__);
}
