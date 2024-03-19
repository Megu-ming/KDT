#pragma once
#include <iostream>
#include <chrono>
#include <format>
#include <array>   
#include <functional>
#include <vector> 
#include <boost/pool/pool.hpp> 
#include <boost/pool/object_pool.hpp>

using namespace std;

// 고정 사이즈 Memory Pool
class FMemoryPool
{
public:
	FMemoryPool(const size_t InBlockSize,
		const size_t InMaxCount)
		: BlockSize(InBlockSize)
		, MaxCount(InMaxCount)
	{
		const size_t Align = 8;
		// 11
		const size_t AlignedBlockSize = BlockSize > Align ? (BlockSize + Align - (BlockSize % Align)) : Align;
		const size_t MemorySize = AlignedBlockSize * MaxCount;
		// 제대로 하려면 얼라인먼트까지 고려해야 한다.
		// StartAddress = ::malloc(MemorySize);
		StartAddress = ::_aligned_malloc(MemorySize, Align);
		MemoryBlock.reserve(MaxCount);
		for (size_t i = 0; i < MaxCount; ++i)
		{
			MemoryBlock.push_back((uint8_t*)StartAddress + i * AlignedBlockSize);
		}
	}

	void* malloc()
	{
		if(MemoryBlock.empty())
			return nullptr;

		void* Pointer = MemoryBlock.back();
		MemoryBlock.pop_back();
		return Pointer;
	}

	void free(void* InMemory)
	{
		MemoryBlock.push_back(InMemory);
	}

	~FMemoryPool()
	{
		if (StartAddress)
		{
			// ::free(StartAddress);
			::_aligned_free(StartAddress);
		}
	}

private:
	const size_t BlockSize;
	const size_t MaxCount;
	void* StartAddress = nullptr;
	vector<void*> MemoryBlock;
};

template<class T>
class FObjectPool : public FMemoryPool
{
public:
	FObjectPool(const size_t InMaxObjectCount)
		:FMemoryPool(sizeof(T), InMaxObjectCount)
	{
	}
	
	template<class... Args>
	T* construct(Args... InArgs)
	{
		T* ret = reinterpret_cast<T*>(FMemoryPool::malloc());
		// std::forward : lvalue -> lvalue, rvalue -> rvalue
		// std::move : rvalue로 전달(cast)
		new(ret)T(forward<Args>(InArgs)...);

		return ret;
	}

	void destroy(T* const chunk)
	{
		chunk->~T();
		FMemoryPool::free(chunk);
	}
};