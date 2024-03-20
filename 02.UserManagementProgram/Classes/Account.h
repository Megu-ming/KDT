#pragma once
#include "MISC/Headers.h"

struct FAccount
{
	FAccountName ID;
	string Password;
	FAccount() = default;
	FAccount(string_view InID, string_view InPassword)
		:ID(InID), Password(InPassword) {}

	// void Save();
	// void Load();

	bool IsEmpty() const
	{
		const bool bID = ID.empty();
		const bool bPassword = Password.empty();

		// 둘 중 하나라도 비어있으면 true
		// 둘 다 차있으면 false
		return bID || bPassword;
	}

	// 예외로 IsEmpty가 true인 경우 무조건 return false 
	bool IsEqual(const FAccount& InAccount) const
	{
		return *this == InAccount;
	}

	// 예외로 IsEmpty가 true인 경우 무조건 return false 
	bool operator==(const FAccount& InAccount) const
	{
		if (IsEmpty())
			return false;
		const bool bID = ID == InAccount.ID;
		const bool bPassword = Password == InAccount.Password;

		return bID && bPassword;
	}

	bool operator!=(const FAccount& InAccount) const
	{
		return !(*this == InAccount);
	}
};

class FAccountSaveLoader
{
	friend class FDataBase;
protected:
	FAccountSaveLoader(FAccount& InAccount, rapidjson::Value& InValue)
		: Account(InAccount), AccountValue(InValue) {}

	void Save(rapidjson::Document::AllocatorType& InAllocator);
	void Load();

private:
	FAccount& Account;
	rapidjson::Value& AccountValue;
};

class FAccountSaveEvent final : public FAccountSaveLoader
{
	friend class FDataBase;
private:
	FAccountSaveEvent(FAccount& InAccount, rapidjson::Value& InValue
	, rapidjson::Document::AllocatorType& InAllocator)
		: FAccountSaveLoader(InAccount,InValue)
		,Allocator(InAllocator)
	{
		Save(Allocator);
	}
private:
	rapidjson::Document::AllocatorType& Allocator;
};

class FAccountLoadEvent final : public FAccountSaveLoader
{
	friend class FDataBase;
private:
	FAccountLoadEvent(FAccount& InAccount, rapidjson::Value& InValue)
		: FAccountSaveLoader(InAccount, InValue)
	{
		Load();
	}
};