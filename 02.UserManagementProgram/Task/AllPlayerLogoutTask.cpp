#include "AllPlayerLogoutTask.h"
#include "Classes/LoginSession.h"

FAllPlayerLogoutTask::FAllPlayerLogoutTask()
{
	GLoginSession.AllPlayerLogout();
}
