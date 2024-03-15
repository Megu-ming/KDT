#include "Function.h"


int GA = 10;
std::shared_ptr<FStruct> GSharedStruct{ std::make_shared<FStruct>() };

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// _CrtSetBreakAlloc(000);

	// Stack memory
	{
		int i1{ 1 };
		int i2{ 2 };
		int i3{ 3 };
		// Stack				// Heap
		// [4byte]i1{1}
		// [4byte]i2{2}
		// [4byte]i3{3}

		i1 = 10;
		// Stack				// Heap
		// [4byte]i1{10}
		// [4byte]i2{2}
		// [4byte]i3{3}
	}
	// Pointer, 동적 할당
	{
		int* Pointer{ nullptr };
		// Stack				// Heap
		// [8byte]Pointer{0}

		Pointer = new int{ 444 };
		// Stack								// Heap
		// [8byte]Pointer{0xHeapAddress}------->[4byte] *Pointer{444}
		*Pointer = 555;
		// [8byte]Pointer{0xHeapAddress}------->[4byte] *Pointer{555}
		delete Pointer;
		// Debug모드에서는 delete하는 경우 삭제한 영역이라는 의미로
		// 0x8123 으로 바꿔준다
		// [8byte]Pointer{0xHeapAddress}------->
		Pointer = nullptr;
		// [8byte]Pointer{0}
	}
	// Pointer, 지역 변수
	{
		int A = 0;
		int* ptr = &A;
		// Stack						
		// [4byte]A{0}
		// [4byte]padding memory
		// [8byte]A{0xA StackAddress}

		A = 100;
		// [4byte]A{100}
		// [4byte]padding memory
		// [8byte]A{0xA StackAddress}
		*ptr = 1000;
		// [4byte]A{1000}
		// [4byte]padding memory
		// [8byte]A{0xA StackAddress}
	}
	// Pointer, 전역 변수
	{
		int* Pointer = &GA;
		// Stack									// Data
		// [8byte]Pointer{0xGA DataAddress}------->[4byte]GA{10}
		*Pointer = 1000;
		// [8byte]Pointer{0xGA DataAddress}------->[4byte]GA{1000}
	}
	// Double Pointer
	{
		int** DoublePtr{ nullptr };
		// Stack							
		// [8byte]Pointer{0}

		DoublePtr = new int*;
		// Stack								// Heap
		// [8byte]Pointer{0xHeapAddress}------->[8byte] *DoublePtr{trash}

		*DoublePtr = new int{ 10 };
		// Stack								// Heap
		// [8byte]Pointer{0xHeapAddress}------->[8byte] *DoublePtr{0xHeapAddress}
		//											ㄴ> [4byte]**DoublePtr{10}

		**DoublePtr = 100;
		// Stack								// Heap
		// [8byte]Pointer{0xHeapAddress}------->[8byte] *DoublePtr{0xHeapAddress}
		//											ㄴ> [4byte]**DoublePtr{100}

		delete* DoublePtr;
		// Stack								// Heap
		// [8byte]Pointer{0xHeapAddress}------->[8byte] *DoublePtr{0xHeapAddress}

		delete DoublePtr;
		// Stack								// Heap
		// [8byte]Pointer{0xHeapAddress}------->
		DoublePtr = nullptr;
		// Stack								// Heap
		// [8byte]Pointer{0}
	}
	// Double Pointer tip (COM; Component Object Model)
	{
		int* Pointer1 = nullptr;
		int* Pointer2 = nullptr;
		// Stack							// Heap
		// [8byte]Pointer1{0}
		// [8byte]Pointer2{0}
		//AllocateWrong(Pointer1, Pointer2);

		int* InTarget1 = Pointer1;
		int* InTarget2 = Pointer2;
		// Stack							// Heap
		// [8byte]Pointer1{0}
		// [8byte]Pointer2{0}
		// [8byte]InTarget1{0}
		// [8byte]InTarget2{0}
		InTarget1 = new int;
		InTarget2 = new int;
		// Stack							// Heap
		// [8byte]Pointer1{0}
		// [8byte]Pointer2{0}
		// [8byte]InTarget1{0xHeapAddress}->[4byte]*InTarget1{trash}
		// [8byte]InTarget2{0xHeapAddress}->[4byte]*InTarget2{trash}
		delete InTarget1;
		delete InTarget2;

		// Correct Case
		{
			int* Pointer1 = nullptr;
			int* Pointer2 = nullptr;
			// Stack								// Heap
			// [8byte]Pointer1{0}
			// [8byte]Pointer2{0}
			AllocateCorrect(&Pointer1, &Pointer2);
			// Stack								// Heap
			// [8byte]Pointer1{0xHeapAddress}
			// [8byte]Pointer2{0xHeapAddress}
			// [8byte]InTarget1{&Pointer1}			[4byte]*InTarget1->Pointer1{trash}
			// [8byte]InTarget2{&Pointer2}			[4byte]*InTarget2->Pointer2{trash}

			// Delete Pointer
			Delete(&Pointer1);
			Delete(&Pointer2);
		}
	}
	// 배열과 메모리 할당
	{
		// 배열
		{
			int Array[5]{ 3,4,5 };
			// Stack
			// Array[0]{3}
			// Array[1]{4}
			// Array[2]{5}
			// Array[3]{0}
			// Array[4]{0}
		}
		// 배열 동적 할당
		{
			int* Pointer = new int[5];
			for (int i = 0; i < 5; ++i)
			{
				Pointer[i] = i;
				*(Pointer + i) = i + 1;
			}
			// Stack							// Heap
			// [8byte]Pointer{HeapAddress}----->Array[0]{1}
			// 									Array[1]{2}
			// 									Array[2]{3}
			// 									Array[3]{4}
			// 									Array[4]{5}
		}
		// 2차원 배열
		{
			char Array[3][2]{};
			for (int i = 0; i < 3; ++i)
				for (int j = 0; j < 2; ++j)
				{
					Array[i][j] = char(i * 2 + j);
				}
		}
		// 함수에 포인터로 배열 전달
		{
			int Array[100]{};
			InitArray(Array, 100);

			int Array2[500]{};
			InitArray(Array2, 500);
		}
		// STL(Standard Template Library)에 있는 자료구조
		{
			std::vector<int> Vector;
			Vector.resize(10);

			/*for (int i = 0; i < 10; ++i)
			{
				Vector[i] = i;
			}*/
			InitArray(Vector);
			InitArray(&Vector);
		}
		// Sum
		{
			int Result = 0;
			std::vector<int> Numbers{ 1,2,3,4,5,6 };
			Sum(Numbers, &Result);
		}
		// Swap
		{
			int A = 10;
			int B = 360;
			Swap(A, B);
		}
		// Smart Pointer
		{
			using namespace std;
			// unique_ptr
			{
				unique_ptr<int> Unique = make_unique<int>(10);
				*Unique = 1000;
			}
			{
				unique_ptr<FStruct> Unique = make_unique<FStruct>();
				Unique->Hello();
				UniqueParam(Unique);
			}
			// shared_ptr
			{
				shared_ptr<int> Shared{ make_shared<int>(100) };
				*Shared = 1000;

				shared_ptr<FStruct> SharedStruct1{ make_shared<FStruct>() };
				shared_ptr<FStruct> SharedStruct2{ make_shared<FStruct>(999) };
				shared_ptr<FStruct> SharedStruct3{ make_shared<FStruct>(100.f) };

				int Count = SharedStruct1.use_count();
				GSharedStruct = SharedStruct1;
				Count = SharedStruct1.use_count();
			}
		}
	}

#pragma region auto
	{
		// 컴파일러가 타입을 추론할 수 있는 경우 타입을 추론해주는 기능
		// 컴파일러가 타입을 추록해야하기 때문에 컴파일 시간이 늘어나는 단점
		// 전체 빌드 시간이 늘어남; 하지만 소소하게 쓰면 의미없는 시간
		auto intA = 10;
		auto floatA = 10.f;
		auto doubleA = 10.0000;

	}
#pragma endregion
	// auto 복붙 필요
#pragma region 함수 포인터(Function Pointer)
	{
		// 함수도 주소가 부여되어 있다.
		// C++에서는 함수의 주소를 구해서 변수처럼 사용할 수 있습니다.

		//						리턴타입(함수라는의미)(입력타입)
		using FFunctionPointer = bool(*)();
		bool(*Test)() = ReturnTrue;				 // 방법 1
		FFunctionPointer Test2 = ReturnTrue;	 // 방법 2

		bool bResult = Test();
		bool bResult2 = Test2();

		Test2 = ReturnFalse;
		bool bResult3 = Test2();

		auto Function = ReturnFalse;
	}
	{
		std::function<bool()> Function = ReturnTrue;
		std::function Function2 = ReturnFalse;
		Function();
		Function2();
	}
	{
		std::function Function = SumFunction;
		int Result = Function(1, 2);

		auto Function2 = SumFunction;
		int Result2 = Function2(1, 2);

	}
	{
		FStruct Instance;
		Instance.SetValue(1000);
		Instance.Hello();
		auto Function = std::bind(&FStruct::Hello, &Instance, std::placeholders::_1);
	}
#pragma endregion
#pragma region 람다(lambda)
	{
		// 이름없는 함수라고 부르기도 함
		// void Func()
		[]()
			{
				std::cout << "Lambda Function!\n";
			};
		[]()
			{
				std::cout << "Lambda Function!\n";
			}();

		std::function Lambda = []()
			{
				std::cout << "Lambda Function!\n";
			};
		Lambda();

		{
			std::function Lambda = [](const int InValue)
				{
					std::cout << "Lambda Function!\n";
					std::cout << InValue << std::endl;
				};
			Lambda(10);
			Lambda(50);
		}
		{												
														// return type
			std::function Lambda = [](const int InValue)->int
				{
					std::cout << "Lambda Function!\n";
					std::cout << InValue << std::endl;
					return InValue + 100;
				};
			int val1 = Lambda(10);
			int val2 = Lambda(50);
		}
		{
			int a = 10, b = 20, c = 30;
			// [] 안에 외부 변수를 넣으면 해당 변수를 capture해서
			// 함수 내부에서 사용 가능하다.
			// [a]와 같이 사용하는 경우 a를 값으로 capture한다.
			std::function Lambda = [a, b, &c](const int InValue)->int
				{
					std::cout << "Lambda Function!\n";
					std::cout << InValue << std::endl;
					std::cout << a << std::endl;
					std::cout << b << std::endl;
					std::cout << c << std::endl;
					// a=100; // 값으로 capture하면 해당 값을 수정할 수 없다.
					c = 100;
					return InValue + 100;
				};
			int val1 = Lambda(10);
			int val2 = Lambda(50);
		}
		{
			int a = 10, b = 20, c = 30;
			// [=]을 사용하면 현재 캡쳐 가능한 변수를 값으로 가져온다.
			std::function Lambda = [=, &c](const int InValue)->int
				{
					std::cout << "Lambda Function!\n";
					std::cout << InValue << std::endl;
					std::cout << a << std::endl;
					std::cout << b << std::endl;
					std::cout << c << std::endl;
					c += 100;
					return InValue + 100;
				};
			int val1 = Lambda(10);
			int val2 = Lambda(50);
		}
		{
			int a = 10, b = 20, c = 30;
			// [&]을 사용하면 현재 캡쳐 가능한 변수를 참조로 가져온다.
			std::function Lambda = [&](const int InValue)->int
				{
					std::cout << "Lambda Function!\n";
					std::cout << InValue << std::endl;
					std::cout << a << std::endl;
					std::cout << b << std::endl;
					std::cout << c << std::endl;
					c += 100;
					return InValue + 100;
				};
			int val1 = Lambda(10);
			int val2 = Lambda(50);
		}
		{
			FunctionFunction(Test);

			FunctionFunction([]() {
				for (int i = 0; i < 10; ++i)
				{
					std::cout << std::format("Lambda! :{}\n", i);
				}
				});
		}
	}
#pragma endregion
#pragma region random, sort
	{
		// 컴퓨터에서 random함수는 진짜 random이 아닐 수 있습니다.
		// 좋은 random 함수를 사용해야 더 random에 가깝다

		std::random_device RD;
		std::mt19937 Gen(RD());
		std::uniform_int_distribution<int> Dist(0, 999);
		int RandomValue = Dist(Gen);

		std::vector<int> randValue;
		randValue.resize(100);
		for (int& i : randValue)
		{
			i = Dist(Gen);
		}

		// 오름차순 정렬
		std::sort(randValue.begin(), randValue.end(), std::less<int>{});
		// 내림차순 정렬
		std::sort(randValue.begin(), randValue.end(), std::greater<int>{});
	}
#pragma endregion
}