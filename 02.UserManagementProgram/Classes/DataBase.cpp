#include "DataBase.h"
#include "Classes/Player.h"

FDataBase GDataBase;

FAccount* FDataBase::CreateAccount(const FAccount& InAccount)
{
	if (InAccount.IsEmpty())
	{
		// _ASSERT(false && "계정 정보가 비어 있습니다.");
		return nullptr;
	}

	// 이미 있는 아이디라면 : 요청 반려
	FAccount* Account = FindAccount(InAccount.ID);
	if (Account)
	{
		// _ASSERT(false && "이미 해당 계정이 있습니다!");
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

	AccountMap.erase(InAccount.ID);

	string DeleteFileCmd = "del /q .\\PlayerInfo\\" + InAccount.ID + ".json";
	system(DeleteFileCmd.c_str());

	return true;
}

FDataBase::FDataBase()
{
	LoadAccount();
}

FDataBase::~FDataBase()
{
	SaveAccount();
}

void FDataBase::SaveAccount()
{
	rapidjson::Document Doc{ rapidjson::kObjectType };
	rapidjson::Document::AllocatorType& Allocator = Doc.GetAllocator();

	rapidjson::Value Array{ rapidjson::kArrayType };
	for (auto& It : AccountMap)
	{
		rapidjson::Value Player{ rapidjson::kObjectType };
		FAccountSaveEvent Save(It.second, Player, Allocator);
		Array.PushBack(Player, Allocator);
	}

	Doc.AddMember("AccountInfo", Array, Allocator);

	rapidjson::StringBuffer Buffer;
	rapidjson::Writer<rapidjson::StringBuffer> Writer(Buffer);
	Doc.Accept(Writer);
	string Json(Buffer.GetString(), Buffer.GetSize());

	ofstream File("AccountInfo.json");
	File << Json;
}

void FDataBase::LoadAccount()
{
	ifstream File("AccountInfo.json");
	if (!File.is_open())
		return;

	string Json;
	string templine;
	while (getline(File, templine))
	{
		Json += templine;
	}
	if (Json.empty())
		return;

	rapidjson::Document Doc(rapidjson::kObjectType);
	Doc.Parse(Json.data());

	const bool bAccountInfo = Doc.HasMember("AccountInfo");
	_ASSERT(bAccountInfo);
	if (bAccountInfo)
	{
		rapidjson::Value& Array = Doc["AccountInfo"];
		_ASSERT(Array.IsArray());
		if (Array.IsArray())
		{
			const rapidjson::SizeType Size = Array.Size();
			for (rapidjson::SizeType i = 0; i < Size; ++i)
			{
				FAccount NewAccount;
				rapidjson::Value& AccountValue = Array[i];
				FAccountLoadEvent(NewAccount, AccountValue);
				FAccount* Account = CreateAccount(NewAccount);
				if (!Account)
				{
					// log
					_ASSERT(false);
				}
			}
		}
	}
}

bool FDataBase::SavePlayer(FPlayer& InPlayer)
{
	FPlayerSaveLoader PlayerSaveLoader(InPlayer);
	return PlayerSaveLoader.Save();
}

bool FDataBase::LoadPlayer(const FAccountName& InAccountName, FPlayer& outPlayer)
{
	FPlayerSaveLoader PlayerSaveLoader(outPlayer);
	return PlayerSaveLoader.Load(InAccountName);
}
