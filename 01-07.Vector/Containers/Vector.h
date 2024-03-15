#pragma once

namespace KDT
{
	int Test() { return 5; }

	template<typename T>
	class FVectorIterator
	{
	public:
		FVectorIterator() = default;
		FVectorIterator(const FVectorIterator& i) = default;
		FVectorIterator(T* InPointer) : Pointer(InPointer) {}
		

		// 선행 증가
		FVectorIterator& operator++()
		{
			if (Pointer)
			{
				++Pointer;
			}
			return *this;
		}

		// 후행 증가
		FVectorIterator operator++(int)
		{
			FVectorIterator Temp = *this;
			FVectorIterator::operator++();
			return Temp;
		}

		// 선행 감소
		FVectorIterator& operator--()
		{
			if (Pointer)
			{
				--Pointer;
			}
			return *this;
		}

		// 후행 감소
		FVectorIterator operator--(int)
		{
			FVectorIterator Temp = *this;
			FVectorIterator::operator--();
			return Temp;
		}

		bool operator==(const FVectorIterator& InIter)
		{
			return Pointer == InIter.Pointer;
		}

		bool operator!=(const FVectorIterator& InIter)
		{
			return Pointer != InIter.Pointer;
		}

		T& operator*() const
		{
			return *Pointer;
		}

		T* operator->() const
		{
			return Pointer;
		}

	private:
		T* Pointer = nullptr;
	};

	template<typename T>
	class vector
	{
	public:
		using iterator = FVectorIterator<T>;

		_NODISCARD_EMPTY_MEMBER _CONSTEXPR20 iterator begin() noexcept
		{
			return iterator(Array);
		}

		_NODISCARD_EMPTY_MEMBER _CONSTEXPR20 iterator end() noexcept
		{
			return iterator(Array + Size);
		}

	public:
		void push_back(const T& InData)
		{
			if (IsFull())
			{
				reserve(Capacity * 2);
			}

			// Array[Size] = InData;
			new(Array + Size)T(InData);
			Size++;
		}

		void push_back(T&& InData)
		{
			if (IsFull())
			{
				reserve(Capacity * 2);
			}

			// Array[Size] = InData;
			new(Array + Size)T(std::move(InData));
			Size++;
		}

		void reserve(const size_t InSize)
		{
			// 최소 capacity
			static const size_t MinSize = 1;
			// end까지 고려해서 + 1 해줌
			size_t NewSize = std::max(MinSize, InSize) + 1;

			// T* NewArray = new T[NewSize];
			// new안하는 이유
			// struct나 class같은 경우는 호출할때마다 생성자 호출되니까
			T* NewArray = (T*)malloc(sizeof(T) * NewSize);

			if(!empty())
			{
				for (size_t i = 0; i < Size; ++i)
				{
					// 원본 size보다 작은 size로 resize하는 경우
					if (i >= (NewSize - 1))
					{
						for (int k = i; k < Size; ++k)
							Array[k].~T();
						Size = i;
						break;
					}

					// NewArray[i] = std::move(Array[i]);
					new(NewArray + i)T(std::move(Array[i]));
					Array[i].~T();
				}
			}

			if (Array)
			{
				// delete[] Array;
				free(Array);
				Array = nullptr;
			}

			Array = NewArray;
			Capacity = NewSize - 1;
		}

		void resize(const size_t InSize)
		{
			if (InSize == 0)
			{
				clear();
				return;
			}

			reserve(InSize);
			for (size_t i = Size; i < InSize; ++i)
			{
				push_back({});
			}
		}

		_NODISCARD_EMPTY_MEMBER _CONSTEXPR20 bool empty() const { return Size == 0; }

		void clear()
		{
			if (Array == nullptr) { return; }

			for (int i = 0; i < Size; ++i)
				Array[i].~T();

			// delete[] Array;
			free(Array);
			Array = nullptr;

			Size = 0;
			Capacity = 0;
		}

		_NODISCARD size_t size() const { return Size; }
		_NODISCARD size_t capacity() const { return Capacity; }

		_NODISCARD T& operator[](const size_t Index) const { return Array[Index]; }

	public:
		vector() = default;
		~vector() { clear(); }
	private:
		_NODISCARD bool IsFull() const { return Size == Capacity; }

	private:
		T* Array = nullptr;
		size_t Size = 0;
		size_t Capacity = 0;
	};
}