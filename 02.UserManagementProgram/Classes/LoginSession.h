#pragma once
#include "MISC/Headers.h"
#include "Player.h"
#include "Account.h"

class FLoginSession
{
public:
	pair<FPlayer*, const char*> Login(const FAccount& InAccount);
	bool IsLogin(const FAccountName& InAccountName);

	pair<bool, const char*> LogOut(const FAccount& InAccount);

	const unordered_map<FAccountName, FPlayer> const GetPlayerMap() { return PlayerMap; }

private:
	unordered_map<FAccountName, FPlayer> PlayerMap;
};

inline FLoginSession GLoginSession;