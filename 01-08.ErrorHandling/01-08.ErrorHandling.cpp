#include <iostream>
#include <cassert>

// error code 방식
// return 0; nullptr error
// return 1; 성공
int Function(int* InPointer)
{
	if (InPointer == nullptr)
		return 0;
	*InPointer = 100;

	return 1;
}

enum EErrorCode : uint8_t
{
	Nullptr = 0,
	Success = 1,
	// ...
};

EErrorCode Function2(int* InPointer)
{
	
	if (InPointer == nullptr)
	{
		// check, ensure <-- unreal engine version assert
		// _ASSERT(false);
		return EErrorCode::Nullptr;
	}
	*InPointer = 100;
	return EErrorCode::Success;
}

void FunctionException(int* InPointer) // noexcept // 예외를 던지지 않겠다. (이러고 throw하면 크래시 발생
{
	if (InPointer == nullptr)
	{
		//throw "InPointer is nullptr";
		throw 0.f;
	}
	*InPointer = 100;
}

class FClass
{
public:
	FClass(int i) // noexcept
	{
		if (i == 0)
		{
			throw 0;
		}
	}
};

int main()
{
	// 기본형
	{
		int Value = 0;
		int ErrorCode = Function(nullptr/*&Value*/);
		switch (ErrorCode)
		{
		case 0:
			std::cout << "input value is nullptr\n";
			break;
		case 1:
			std::cout << "성공!\n";
			break;
		}
	}
	// enum 활용
	{
		int Value = 0;
		EErrorCode ErrorCode = Function2(nullptr/*&Value*/);
		/*if (ErrorCode == EErrorCode::Nullptr)
		{
			return;
		}*/
		switch (ErrorCode)
		{
		case Nullptr:
			std::cout << "input value is nullptr\n";
			break;
		case Success:
			std::cout << "성공!\n";
			break;
		default:
			break;
		}
	}
	// exception 활용
	{
		try
		{
			int Value = 0;
			FunctionException(&Value);
			FClass Class(1);
			FClass Class2(0);

			FunctionException(nullptr);
		}
		catch (const char* Error)
		{
			std::cout << Error << std::endl;
		}
		catch (int error)
		{
			std::cout << error << std::endl;
		}
		catch (...)
		{
			std::cout << "Unknown Error!\n";
		}
	}
}