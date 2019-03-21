// Copyright 2019 Radon Project All Rights Reserved.

#ifndef RADON_ARRAY_H
#define RADON_ARRAY_H

#include "RadonCore.h"
#include "Allocator.h"
#include "Subset.h"

#define RADON_ARRAY_MAX_ALLOCATION_SIZE	SIZE_MAX

using namespace Radon::Memory;

namespace Radon
{
	struct RADON_API SArrayIterator
	{

	};

	struct RADON_API SArrayConstIterator
	{

	};

	// + TConcurrentArray?
	template <typename T, typename Allocator, typename = TEnableIf<TIsDerivedFrom<Allocator, IAllocator>>>
	class TArray
	{
		typedef TArray<T> MyType;

	public:
		typedef T												ElementType;
		typedef Allocator										AllocatorType;
		typedef struct SArrayIterator							IteratorType;
		typedef struct SArrayConstIterator						ConstIteratorType;
		typedef TSubset<TArray, ElementType, AllocatorType>		SubsetType;

		static const TIndex StartIndex = (TIndex)0;
		static const TIndex NPos = (TIndex)-1;

	public:

		TArray()
			: m_alloc(),
			  m_pData(nullptr),
			  m_size(0),
			  m_capacity(0)
		{

		}

		explicit TArray(const AllocatorType &alloc)
			: m_alloc(alloc),
			  m_pData(nullptr),
			  m_size(0),
			  m_capacity(0)
		{

		}

		explicit TArray(TSize size, const AllocatorType &alloc)
		{
			m_pData = Memory::AllocateNewArray<ElementType>(alloc);
		}

		TArray(TSize size, const ElementType &value, const AllocatorType &alloc);
		TArray(const MyType &other);
		TArray(const MyType &other, const AllocatorType &alloc);
		TArray(MyType &&other);
		TArray(MyType &&other, const AllocatorType &alloc);
		TArray(std::initializer_list<ElementType> initList, const AllocatorType &alloc);
		template<typename InputIterator>
		TArray(InputIterator first, InputIterator last, const AllocatorType &alloc);

		~TArray();

		MyType& operator =(const MyType &other);
		MyType& operator =(MyType &&other);
		MyType& operator =(std::initializer_list<ElementType> initList);

		/* Helper Functions */
		
		TSize GetElementSize() const;
		TSize GetAllocatedSize() const;
		bool ValidateIndex(TIndex index) const;
		bool ValidateAddress(const ElementType *address);

		/* Public Interface */

		TIndex Add(const ElementType &newElement);
		TIndex Add(ElementType &&newElement);
		TIndex Add(Iterator first, Iterator last);
		TIndex Add(std::initializer_list<ElementType> initList);

		template <class... Args>
		ElementType& AddConstruct(Args &&...args);

		TIndex Insert(TIndex index, const ElementType &item);
		TIndex Insert(TIndex index, ElementType &&item);
		TIndex Insert(TIndex index, std::initializer_list<ElementType> initList);
		template <typename InputIterator>
		TIndex Insert(TIndex index, InputIterator first, InputIterator last);

		template <class... Args>
		ElementType& InsertConstruct(TIndex index, Args &&...args);

		void Remove(const ElementType &item);
		void RemoveAt(TIndex index);
		void RemoveRange(TIndex startIndex, TIndex endIndex);
		// RemoveSwap?
		// RemoveSwapIf?

		template <typename Predicate>
		void RemoveIf(Predicate filter, TSize num = NPos);

		bool IsEmpty() const;
		TSize Size() const;
		TSize Capacity() const;

		void Resize(TSize newSize);
		void Reserve(TSize num);
		void Shrink();
		void Clear();

		ElementType& operator[](TIndex index);
		ElementType& At(TIndex index);
		const ElementType& operator[](TIndex index) const;
		const ElementType& At(TIndex index) const;

		TIndex Find(const ElementType &item) const;
		TIndex FindLast(const ElementType &item) const;
		template <typename Predicate>
		TIndex FindIf(Predicate filter) const;
		template <typename Predicate>
		TIndex FindLastIf(Predicate filter) const;

		bool Contains(const ElementType &item) const;
		template <typename Predicate>
		bool ContainsIf(Predicate filter) const;

		template <typename Consumer>
		void ForEach(Consumer action);

		template<typename Predicate>
		SubsetType Filter(Predicate filter);
		template<typename Predicate>
		const SubsetType Filter(Predicate filter) const;

		ElementType* Data();
		const ElementType* Data() const;

		ElementType& Front();
		ElementType& Back();
		const ElementType& Front() const;
		const ElementType& Back() const;

		AllocatorType& GetAllocator();
		const AllocatorType& GetAllocator() const;
		template<typename OtherAllocator, typename = TEnableIf<TIsDerivedFrom<OtherAllocator, AllocatorType>>>
		void SetAllocator(const OtherAllocator &alloc);

		IteratorType Iterator();
		ConstIteratorType ConstIterator();

		FORCEINLINE ElementType* Allocate(TSize num)
		{
#if RADON_ENABLE_ASSERTION
#endif
		}

		FORCEINLINE void Deallocate(ElementType *ptr)
		{

		}

	private:
		AllocatorType m_alloc;
		ElementType *m_ptr;
		TSize m_size;
		TSize m_capacity;
	}; // TArray


/*	template <typename T, typename A>
	FORCEINLINE TArray<T, A>::TArray()
		: m_alloc(),
		  m_pData(nullptr),
		  m_size(0),
		  m_capacity(0)
	{

	}

	template <typename T, typename Allocator>
	explicit TArray<T, Allocator>::TArray(const AllocatorType &alloc)
		: m_alloc(alloc),
		  
	{

	}

	template <typename T, typename Allocator>
	explicit TArray<T, Allocator>::TArray(TSize size, const AllocatorType &alloc)
	{

	}

	template <typename T, typename Allocator>
	TArray<T, Allocator>::TArray(TSize size, const ElementType &value, const AllocatorType &alloc)
	{

	}

	template <typename T, typename Allocator>
	TArray<T, Allocator>::TArray(const MyType &other)
	{

	}

	template <typename T, typename Allocator>
	TArray<T, Allocator>::TArray(const MyType &other, const AllocatorType &alloc)
	{

	}

	template <typename T, typename Allocator>
	TArray<T, Allocator>::TArray(MyType &&other)
	{

	}

	template <typename T, typename Allocator>
	TArray<T, Allocator>::TArray(MyType &&other, const AllocatorType &alloc)
	{

	}

	template <typename T, typename Allocator>
	TArray<T, Allocator>::TArray(std::initializer_list<ElementType> initList, const AllocatorType &alloc)
	{

	}

	template <typename T, typename Allocator, typename InputIterator>
	TArray<T, Allocator>::TArray(InputIterator first, InputIterator last, const AllocatorType &alloc)
	{

	} */
}

#endif