#include "Function.h"



void AllocateWrong(int* InTarget1, int* InTarget2)
{
	InTarget1 = new int;
	InTarget2 = new int;
	
}

void AllocateCorrect(int** InTarget1, int** InTarget2)
{
	*InTarget1 = new int;
	*InTarget2 = new int;
}

void Delete(int** InTarget)
{
	delete *InTarget;
}

void InitArray(int* const InArray, const int size)
{
	for (int i = 0; i < size; ++i)
	{
		InArray[i] = i;
	}
}

void InitArray(std::vector<int>& InArray)
{
	const size_t size = InArray.size();
	for (size_t i = 0; i < size; ++i)
		// i< InArray.size() 
		// size함수를 한번만 호출하도록함
	{
		InArray[i] = i;
	}
}

void InitArray(std::vector<int>* const InArray)
{
	const size_t size = InArray->size();
	for (size_t i = 0; i < size; ++i)
		// i< InArray.size() 
		// size함수를 한번만 호출하도록함
	{
		InArray->at(i) = i; // (*InArray)[i] = i;
	}
}

void Sum(const std::vector<int>& InVector, int* const OutResult)
{
	int result = 0;
	for (int i : InVector)
	{
		result += i;
	}
	*OutResult = result;
}

void Swap(int& InFirst, int& InSecond)
{
	int tmp = InFirst;
	InFirst = InSecond;
	InSecond = tmp;
}

void CustomDeleterInt(int* InPointer)
{
	std::cout << "int delete!\n";
	delete InPointer;
}

void UniqueParam(std::unique_ptr<FStruct>& InParam)
{
	InParam->Hello();
}

bool ReturnTrue()
{
	return true;
}

bool ReturnFalse()
{
	return false;
}

int SumFunction(const int a, const int b)
{
	return a + b;
}

void Test()
{
	std::cout << "Test\n";
}

void FunctionFunction(std::function<void()> InFunction)
{
	std::cout << __FUNCTION__ << std::endl;
	InFunction();
}

FStruct::FStruct(int InA)
	:Value(InA)
{

}

FStruct::FStruct(float InA)
	:Value(InA)
{
}

void FStruct::Hello()
{
	std::cout << "Hello\n";
	std::cout << Value << std::endl;
}