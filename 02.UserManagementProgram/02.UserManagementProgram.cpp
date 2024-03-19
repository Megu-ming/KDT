#include "MISC/Headers.h"
#include "Classes/Account.h"
#include "Classes/DataBase.h"

// C++ 문법을 사용해서 간단한 
// - 회원가입, 회원탈퇴
// - 로그인, 로그아웃
// - 접속중인 유저 표시
// - 입력 인터페이스 

// 회원 정보 관련
// - class FDataBase
// 회원 정보
// - struct FAccount

int main()
{
	FAccount Account("Hello", "World");

	FAccount* NewAccount = GDataBase.CreateAccount(Account);
	GDataBase.DeleteAccount(*NewAccount);
	GDataBase.DeleteAccount(Account);
	FAccount* NewAccount2 = GDataBase.CreateAccount(Account);
}