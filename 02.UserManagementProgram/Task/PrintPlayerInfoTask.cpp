#include "PrintPlayerInfoTask.h"
#include "MISC/Utils.h"
#include "Classes/LoginSession.h"

FPrintPlayerInfoTask::FPrintPlayerInfoTask()
{
	FAccountName Name;
	cout << "[------- Pick Player -------]" << endl;
	cout << "-> ";
	cin >> Name;
	auto& PlayerMap = GLoginSession.GetPlayerMap();
	auto It = PlayerMap.find(Name);
	if (It != PlayerMap.end())
	{
		cout << format("{} Info", It->first) << endl;
		cout << format("Level : {}", It->second.GetLevel()) << endl;
	}
	
}
