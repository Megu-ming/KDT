#include "Function.h"
#include <format>

void FunctionName()
{
}

void FunctionName(int a)
{
	//std::cout << "a: " << a << std::endl;
	std::cout << std::format("a: {}\n", a);
}

int AddFunction(int a, int b)
{
	const int Sum = a + b;
	std::cout << std::format("[{}:{}:{}] {} + {} = {}\n", __func__, __FILE__, __LINE__, a, b, Sum);
	return Sum;
}

double AddFunction(double a, double b)
{
	const double Sum = a + b;
	std::cout << std::format("[{}:{}:{}] {} + {} = {}\n", __func__, __FILE__, __LINE__, a, b, Sum);
	return Sum;
}

unsigned long long Factorial(unsigned char f)
{
	if (f == 0)
	{
		return 1;
	}
	else
	{
		return f * Factorial(f - 1);
	}
}

void HasFlag(unsigned char InProperty)
{
	// 1번 속성이 활성화 되어 있나요?
	// 0000 0101
	// 0000 0001
	// --------- AND (둘다 1이면 1, 하나라도 0이면 0)
	// 0000 0001
	// 참
	// if는 0이면 false, 0이 아니면 true
	if (InProperty & EPropertyFlags::EProperty1)
	{
		std::cout << "EPropertyFlags::EProperty1\n";
	}
	if (InProperty & EPropertyFlags::EProperty2)
	{
		std::cout << "EPropertyFlags::EProperty2\n";
	}
	if (InProperty & EPropertyFlags::EProperty3)
	{
		std::cout << "EPropertyFlags::EProperty3\n";
	}
	if (InProperty & EPropertyFlags::EProperty4)
	{
		std::cout << "EPropertyFlags::EProperty4\n";
	}
	if (InProperty & EPropertyFlags::EProperty5)
	{
		std::cout << "EPropertyFlags::EProperty5\n";
	}
	if (InProperty & EPropertyFlags::EProperty6)
	{
		std::cout << "EPropertyFlags::EProperty6\n";
	}
	if (InProperty & EPropertyFlags::EProperty7)
	{
		std::cout << "EPropertyFlags::EProperty7\n";
	}
	if (InProperty & EPropertyFlags::EProperty8)
	{
		std::cout << "EPropertyFlags::EProperty8\n";
	}
}

// int a = Value;
int Function(int a)
{
	a = 10;
	return a;
}

FParam Function(FParam InParam)
{
	for (int i = 0; i < 1000; ++i)
	{
		InParam.Value[i] = i;
	}
	return InParam;
}

void Function(FParam* InParam)
{
	for (int i = 0; i < 1000; ++i)
	{
		InParam->Value[i] = i;
	}
}

void FunctionCallByPointer(int* InParam)
{
	*InParam += 1;
}

void FunctionCallByReference(int& InParam)
{
	InParam += 1;
}

void FunctionCallByReference(FParam& InParam)
{
	for (int i = 0; i < 1000; ++i)
	{
		InParam.Value[i] = i;
	}
}

#include <cassert>
void FunctionWithPointer(int* InPointer)
{
	// debug 모드일때 동작하는 assert는
	// 프로그래머의 명백한 실수를 탐지하기 위해 사용
	//_ASSERT(InPointer != nullptr);
	//if (InPointer == nullptr)
	if (!InPointer)
	{
		//_ASSERT(false);
		return;
	}

	*InPointer += 100;
}

// In: 밖에서 값을 채워서 준다
// Out: 값이 함수 내부에서 바뀌어서 나온다
void Swap(int& InOutFirst, int& InOutSecond)
{
	// Temp = A(10)
	const int Temp = InOutFirst;

	// A(10) = B(100)
	// A = 100
	InOutFirst = InOutSecond;

	// B(100) = Temp(10)
	// B = 10
	InOutSecond = Temp;

	// InOutFirst(A): 100
	// InOutSecond(B): 10
}

void Swap(int* InOutFirst, int* InOutSecond)
{
	// Temp = A(100)
	const int Temp = *InOutFirst;

	// A(100) = B(10)
	// A = 10
	*InOutFirst = *InOutSecond;

	// B(10) = Temp(100)
	*InOutSecond = Temp;

	// InOutFirst(A): 10
	// InOutSecond(B): 100
}

void SeperateOddsAndEvens(const std::array<int, 10>* InNumbers, std::vector<int>* OutOdds, std::vector<int>* OutEvens)
{
	for (int Value : *InNumbers)
	{
		std::cout << Value << std::endl;

		// 홀수 판정
		// 1 / 2 : 몫:0 나머지:1 => 1은 홀수
		// 2 / 2 : 몫:1 나머지:0 => 2는 짝수
		// 3 / 2 : 몫:1 나머지:1 => 3은 홀수
		// 4 / 2 : 몫:2 나머지:0 => 4는 짝수
		if (Value % 2 == 1)
		{
			OutOdds->push_back(Value);
		}
		else
		{
			OutEvens->push_back(Value);
		}
	}
}

void SeperateOddsAndEvens(const std::array<int, 10>& InNumbers, std::vector<int>& OutOdds, std::vector<int>& OutEvens)
{
	for (int Value : InNumbers)
	{
		std::cout << Value << std::endl;

		// 홀수 판정
		// 1 / 2 : 몫:0 나머지:1 => 1은 홀수
		// 2 / 2 : 몫:1 나머지:0 => 2는 짝수
		// 3 / 2 : 몫:1 나머지:1 => 3은 홀수
		// 4 / 2 : 몫:2 나머지:0 => 4는 짝수
		if (Value % 2 == 1)
		{
			OutOdds.push_back(Value);
		}
		else
		{
			OutEvens.push_back(Value);
		}
	}
}

FOddsAndEvens SeperateOddsAndEvens(const std::array<int, 10>& InNumbers)
{
	std::vector<int> Odds, Evens;
	for (int Value : InNumbers)
	{
		std::cout << Value << std::endl;

		// 홀수 판정
		// 1 / 2 : 몫:0 나머지:1 => 1은 홀수
		// 2 / 2 : 몫:1 나머지:0 => 2는 짝수
		// 3 / 2 : 몫:1 나머지:1 => 3은 홀수
		// 4 / 2 : 몫:2 나머지:0 => 4는 짝수
		if (Value % 2 == 1)
		{
			Odds.push_back(Value);
		}
		else
		{
			Evens.push_back(Value);
		}
	}

	// RVO(Return Value Optimaization): 리턴값 최적화
	return FOddsAndEvens(Odds, Evens);
}

void Test(int aa)
{
	aa = 100;
}

void TestReference(int& aa)
{
	aa = 100;
}

void TestPointer(int* aa)
{
	*aa = 1000;
}

int Sum(std::initializer_list<int> InValues)
{
	int Total = 0;
	for (int i : InValues)
	{
		Total += i;
	}
	return Total;
}

int Sum2(std::vector<int> InValues)
{
	int Total = 0;
	for (int i : InValues)
	{
		Total += i;
	}
	return Total;
}