#include "PrintLoginPlayerTask.h"
#include "MISC/Utils.h"
#include "Classes/LoginSession.h"
FPrintLoginPlayerTask::FPrintLoginPlayerTask()
{
	const auto& AccountMap = GLoginSession.GetPlayerMap();
	cout << "[--------- Player ----------]" << endl;
	for (auto& It : AccountMap)
	{
		cout << format("-> Name: {}\n", It.second.GetName());
		cout << format("-> Level: {}\n", It.second.GetLevel());
	}
	cout << "[---------------------------]" << endl;
}