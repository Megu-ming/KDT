#pragma once
#include "MISC/Headers.h"
#include "Player.h"
#include "Account.h"

class FLoginSession
{
public:
	pair<FPlayer*, const char*> Login(const FAccount& InAccount);
	bool IsLogin(const FAccountName& InAccountName);
	FPlayer* GetLoginPlayer(const FAccountName& InAccountName);
	pair<bool, const char*> Logout(const FAccount& InAccount);

	const unordered_map<FAccountName, FPlayer> GetPlayerMap() const { return PlayerMap; }

private:
	friend struct FAllPlayerLogoutTask;
	void AllPlayerLogout();

private:
	unordered_map<FAccountName, FPlayer> PlayerMap;
};

inline FLoginSession GLoginSession;