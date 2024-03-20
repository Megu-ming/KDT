#include "DataBase.h"

FDataBase GDataBase;

FAccount* FDataBase::CreateAccount(const FAccount& InAccount)
{
	if (InAccount.IsEmpty())
	{
		_ASSERT(false && "계정 정보가 비어 있습니다.");
		return nullptr;
	}

	// 이미 있는 아이디라면 : 요청 반려
	FAccount* Account = FindAccount(InAccount.ID);
	if (Account)
	{
		_ASSERT(false && "이미 해당 계정이 있습니다!");
		return nullptr;
	}

	pair Pair = AccountMap.insert(make_pair(InAccount.ID, InAccount));
	if (!Pair.second)
	{
		_ASSERT(false);
		return nullptr;
	}

	return &Pair.first->second;
}

FAccount* FDataBase::FindAccount(const FAccountName& InID)
{
	auto It = AccountMap.find(InID);
	if (It == AccountMap.end())
		return nullptr;

	return &It->second;
}

FAccount* FDataBase::CheckAccount(const FAccount& InAccount)
{
	if (InAccount.IsEmpty())
	{
		_ASSERT(false);
		return nullptr;
	}

	// 해당 ID로 된 account가 있는 지 검사
	FAccount* Account = FindAccount(InAccount.ID);
	if (!Account)
	{	
		// 해당 ID로 계정 정보를 검색할 수 없다
		_ASSERT(false && "해당 ID로 계정 정보를 검색할 수 없다");
		return nullptr;
	}

	// InAccount와 찾아온 계정 정보가 동일한 지 확인
	if (*Account != InAccount)
	{
		// 비밀번호가 일치하지 않습니다!
		_ASSERT(false && "비밀번호가 일치하지 않습니다!");
		return nullptr;
	}

	return Account;
}

bool FDataBase::DeleteAccount(const FAccount& InAccount)
{
	FAccount* Account = CheckAccount(InAccount);
	if (!Account)
	{
		// 해당 계정이 없다면
		_ASSERT(false);
		return false;
	}

	AccountMap.erase(Account->ID);

	return true;
}

FDataBase::FDataBase()
{
	Load();
}

FDataBase::~FDataBase()
{
	Save();
}

void FDataBase::Save()
{
}

void FDataBase::Load()
{
}
