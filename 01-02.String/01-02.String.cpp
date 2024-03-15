#include <iostream>
#include <format>
#include <string>
#include <Windows.h>


int main()
{
#pragma region C스타일의 문자열
	{
		char String1[6] = { "Hello" }; // \0 : 문자열의 끝
		// char[0]{'H'}
		// char[1]{'e'}
		// char[2]{'l'}
		// char[3]{'l'}
		// char[4]{'o'}
		// char[5]{'\0'}

		std::cout << String1 << std::endl;
		String1[0] = 'W';
		String1[1] = 's';
		// String1[9] = 'b'; Buffer Overflow

		char* Pointer = String1;
		// char[0]{'W'}
		// char[1]{'s'}
		// char[2]{'l'}
		// char[3]{'l'}
		// char[4]{'o'}
		// char[5]{'\0'}
		// [8byte] Pointer {0xString1StackAddress};
		*(Pointer + 3) = 'A';	// "WslAo"

		// String1 = String11; 안된다1
		// 장점
		// - 간단하다
		// - 가볍다. 메모리를 필요한 만큼만 사용한다
		// - 저수준(low level)이다. 메모리 조작이 쉽다
		// 단점
		// - 편의 기능(복사,사이즈확인 등)을 관련 기능을 찾거나 구현하려면 별도의 노락이 든다
		// - 찾기 힘든 메모리 관련 버그가 발생하기 쉽다.
		// - C++의 객체지향적인 특성을 활용하지 못한다.

	}
#pragma endregion
#pragma region C++ 문자열(String)
	{
		std::string A = "Hello ";
		std::string B = "World!";
		std::string C = A + B; // Hello World!

		A += B;	// Hello World!
		A.append(B);	// Hello World!World!
	}
	{
		const char* A{ "Hello" };	// Data에
		const char B[]{ "Hello" };	// Stack memory에
		const char* C{ "Hello" };	// Data에 // A, C는 동일한 주소를 가리킴

		if (A == B) // 가리키는 주소가 다르다
		{
			std::cout << "A == B\n";
		}
		else // <<- else로 진입
		{
			std::cout << "A != B\n";
		}
		if (A == C)	// 가리키는 주소가 동일해서 같다
		{
			std::cout << "A == C\n";
		}
		else
		{
			std::cout << "A != C\n";
		}

		bool bSame = true;
		for (int i = 0; i < 5; ++i)
		{
			if (A[i] != B[i])
			{
				bSame = false;
				break;
			}
		}

		if (bSame)
		{
			std::cout << "Same!\n";
		}

		const int Result = strcmp(A, B);
		if (Result == 0)
		{
			std::cout << "Same\n";
		}

		std::string AA{ "Wows" };
		std::string BB{ "Wows" };
		if (AA == BB)
			//if(AA._Equal(BB))
		{
			std::cout << "Same!\n";
			bool b = AA._Equal(BB);
		}
	}
	{
		// - 시간 및 언어 -> 언어 및 지역 -> 기본 언어 설정 -> (국가 또는 지역) -> 관리자 옵션 -> 시스템 로캘 변경(Beta UTF-8)
		// - Visual stduio 우측 상단 -> 파일 -> 다른 이름으로 xx저장 -> 다이얼로그 우측 하단 저장 버튼 오른쪽에 있는
			// 화살표 클릭 -> 인코딩 하여 저장 -> UTF-8로 되어 있는지 확인해야 문제가 없습니다.
		// 한국 로캘에서는 기본적으로 한국어 코드페이지(949)로 되어 있으나 이러면 한글 주석, 문자열 등이
		// 깃 등에 업로드 하면 깨져서 나옵니다.

		// visual studio에서 .editconfig라는 파일을 만들어서 원하는 확장자 파일의 코드 페이지를 설정하면
		// 신규로 만드는 파이르이 경우 해당 코드 페이지를 사용하게 됩니다.

		//TCHAR Char[]{ TEXT("안녕 Hello!") };

		std::wstring String{ L"안녕 Hello!" };
		std::wstring String2{ TEXT("안녕 Hello!") };

		if (String == String2)
		{
			std::cout << "Same!\n";
		}

		std::wstring WString = TEXT("Hello World!");
		if (!WString.empty())
		{
			size_t Size = WString.size();
			const size_t FindIndex = WString.find(TEXT("d!"));

			if (FindIndex != std::wstring::npos)
			{
				std::cout << std::format("d! index = {} \n", FindIndex);
				WString.replace(FindIndex, 2, TEXT("@#"));
			}

			const size_t FindIndex2 = WString.find(TEXT("!!!"));
		}
	}
	// 문자열을 다른 자료형으로 변환
	{
		// 문자열을 정수로(string to int: stoi)
		{
			std::wstring StringNumber{ TEXT("20") };
			int Number = std::stoi(StringNumber);
			std::cout << Number << std::endl;
		}
		// 정수를 문자열로
		{
			std::wstring WString = std::to_wstring(1000);
			std::string String = std::to_string(1000);
			//std::string String2 = 1000;
		}
		// 문자열을 유니코드 문자열
		{
			std::string String = "Hello 한글 こんにちは 哈罗 صباح الخير\n";
			// 필요한 경우 해당 함수를 찾아서 사용하면 된다.
			//std::wstring WString = std::wstring(String.begin(), String.end());
		}
		// 정수를 float로
		{
			std::wstring String{ TEXT("2.35f") };
			// String to Float
			float Float = std::stof(String);
			std::wstring String2 = std::to_wstring(Float);
		}
		{
			class FString : public std::wstring
			{
			public:
				int ToInt() const
				{
					return std::stoi(*this);
				}
			};

			FString String{ TEXT("1024") };
			size_t Size = String.size();
			int Int = String.ToInt();
			wchar_t* Data = String.data();
			Data[0] = TEXT('A');
			String[0] = TEXT('B');
		}
	}
#pragma endregion
#pragma region StringView
	// C++17에 추가된 읽기 전용 string class
	{
		std::wstring String{ TEXT("Hello") };
		// 복사가 발생
		std::wstring String2 = String;
		String2[0] = TEXT('A');

		std::wstring& StringRef = String;
		std::wstring* const StringPtr = &String;
		StringRef[0] = L'W';

		std::wstring_view WStringView = TEXT("Hello");
		// WStringView[0] = TEXT('A'); 수정 불가
		// const wchar_t* Test = WStringView.data();
		WStringView = String;
		auto Function1 = [](const std::wstring InString)
			{
				std::wcout << InString << std::endl;
			};
		auto Function2 = [](const std::wstring_view InStringView)
			{
				std::wcout << InStringView << std::endl;
			};

		Function1(String);
		Function2(WStringView);

	}
#pragma endregion
}