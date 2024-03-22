#pragma once
#include "MISC/Headers.h"

// Account로 로그인을 성공했을 때 생성됨
class FPlayer
{
	friend class FPlayerSaveLoader;
public:
	FPlayer(string_view InName)
		:Name(InName) { }
public:
	string_view GetName() const { return Name; }

	int GetLevel() const { return Level; }
	void SetLevel(const int InLevel) { Level = InLevel; }

private:
	string Name;
	int Level = 0;
};

class FPlayerSaveLoader final
{
	friend class FDataBase;
protected:
	FPlayerSaveLoader(FPlayer& InPlayer)
		: Player(InPlayer) {}

	bool Save();
	bool Load(const FAccountName& InAccountName);

private:
	FPlayer& Player;
};
