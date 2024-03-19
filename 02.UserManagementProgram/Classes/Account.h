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
		const bool bEmpty = IsEmpty();
		if (bEmpty)
			return false;
		const bool bID = ID == InAccount.ID;
		const bool bPassword = Password == InAccount.Password;

		return bID && bPassword;
	}
};

