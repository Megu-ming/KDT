#include "MISC/Headers.h"
#include "Classes/Account.h"
#include "Classes/DataBase.h"
#include "Classes/Engine.h"

// C++ 문법을 사용해서 간단한 
// - [o] 회원가입, 회원탈퇴
// - 로그인, 로그아웃
// - 접속중인 유저 표시
// - [o] 입력 인터페이스 

// 회원 정보 관련
// - class FDataBase
// 회원 정보
// - struct FAccount

int main()
{
	GEngine.Run();
	/*for (int i = 0; i < 5; ++i)
	{
		FAccount Account("Hello" + to_string(i), "World");
		GDataBase.CreateAccount(Account);
	}*/
}