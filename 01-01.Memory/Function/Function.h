#pragma once
#include <vector>
#include <memory>
#include <functional>
#include <iostream>
#include <format>
#include <random>

void AllocateWrong(int* InTarget1, int* InTarget2);
void AllocateCorrect(int** InTarget1, int** InTarget2);
void Delete(int** InTarget);

void InitArray(int* const InArray, const int size);
void InitArray(std::vector<int>& InArray);
void InitArray(std::vector<int>*const InArray);

void Sum(const std::vector<int>& InVector, int* const OutResult);
void Swap(int& InFirst, int& InSecond);

void CustomDeleterInt(int* InPointer);

struct FStruct : public std::enable_shared_from_this<FStruct>
{
	FStruct() = default;
	FStruct(int InA);
	FStruct(float InA);
	FStruct(const FStruct& InOther) = default;
	FStruct& operator=(const FStruct& InOther) = default;
	~FStruct() = default;

	inline void SetValue(int InValue) { Value = InValue; }
	void Hello();

private:
	int Value;
};

void UniqueParam(std::unique_ptr<FStruct>& InParam);

bool ReturnTrue();
bool ReturnFalse();

int SumFunction(const int a, const int b);

void Test();
void FunctionFunction(std::function<void()> InFunction);