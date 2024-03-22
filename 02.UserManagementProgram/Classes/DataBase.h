#pragma once
#include "MISC/Headers.h"
#include "Account.h"

// FAccount의 컨테이너 역할
class FDataBase final
{
	friend struct FLoginTask;
	friend class FLoginSession;
public:
	// 회원 가입
	FAccount* CreateAccount(const FAccount& InAccount);

	// 회원 검색(ID만 찾아옴)
	// ID로 계정 정보를 찾아본다.
	// 찾지 못하면 nullptr 반환
	FAccount* FindAccount(const FAccountName& InID);

	// 회원 가입 여부 검사(ID, Password 모두 일치해야함)
	FAccount* CheckAccount(const FAccount& InAccount);

	// 회원 탈퇴
	bool DeleteAccount(const FAccount& InAccount);
	

public:
	// 실제로 DB에 값을 써야하는 상황이라면
	// 중요한 요청(회원가입과 같은 상황)에는 즉시 DB에 값을 써야 하지만
	// 이 예제는 프로그램이 켜지고 꺼질때 디스크에서 불러오고 저장한다.
	FDataBase();
	~FDataBase();

	const unordered_map<FAccountName, FAccount>& GetAccountMap() const { return AccountMap; }
private:
	void SaveAccount();
	void LoadAccount();

	bool SavePlayer(class FPlayer& InPlayer);
	bool LoadPlayer(const FAccountName& InAccountName, class FPlayer& outPlayer);

private:
	unordered_map<FAccountName, FAccount> AccountMap;
};

// extern 어딘가에 있어
extern FDataBase GDataBase;
// inline FDataBase GDataBase; // dll에서 문제 가능성 있음