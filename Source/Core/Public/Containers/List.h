// Copyright 2019 Radon Project All Rights Reserved.

#ifndef RADON_LIST_H
#define RADON_LIST_H

#include "Allocator.h"
#include "Subset.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once // for faster compilation time
#endif

using namespace Radon::Memory;

namespace Radon
{
	template <typename T>
	struct TListNode
	{
		typedef TListNode<T> MyType;

		FORCEINLINE void AddBefore(MyType *pNode) RADON_NOEXCEPT
		{
			if (pPrev)
			{
				pPrev->pNext = pNode;
			}

			pNode->pPrev = pPrev;
			pNode->pNext = this;
			pPrev = pNode;
		}

		FORCEINLINE void AddAllBefore(MyType *pFirst, MyType *pLast) RADON_NOEXCEPT
		{
			if (pPrev)
			{
				pPrev->pNext = pFirst;
			}

			pFirst->pPrev = pPrev;
			pLast->pNext = this;
			pPrev = pLast;
		}

		FORCEINLINE void AddAfter(MyType *pNode) RADON_NOEXCEPT
		{
			if (pNext)
			{
				pNext->pPrev = pNode;
			}

			pNode->pPrev = this;
			pNode->pNext = pNext;
			pNext = pNode;
		}

		FORCEINLINE void AddAllAfter(MyType *pFirst, MyType *pLast) RADON_NOEXCEPT
		{
			if (pNext)
			{
				pNext->pPrev = pFirst;
			}

			pFirst->pPrev = this;
			pLast->pNext = pNext;
			pNext = pLast;
		}

		FORCEINLINE void Remove() RADON_NOEXCEPT
		{
			if (pPrev)
			{
				pPrev->pNext = pNext;
			}

			if (pNext)
			{
				pNext->pPrev = pPrev;
			}

			pPrev = nullptr;
			pNext = nullptr;
		}

		FORCEINLINE void Replace(MyType *pNode) RADON_NOEXCEPT
		{
			if (pPrev)
			{
				pPrev->pNext = pNode;
			}

			if (pNext)
			{
				pNext->pPrev = pNode;
			}

			pNode->pPrev = pPrev;
			pNode->pNext = pNext;

			pPrev = nullptr;
			pNext = nullptr;
		}


		T value;
		TListNode<T> *pPrev;
		TListNode<T> *pNext;
	};

	template <template <typename>
	          typename Node,
		      typename T, typename Allocator, bool bShared, typename = TEnableIf<TIsDerivedFrom<Allocator, IAllocator>>>
	class TListBase
	{
	public:
		typedef T												ElementType;
		typedef Allocator										AllocatorType;
		typedef Node<T>                                         NodeType;

	protected:

		virtual void Cleanup() = 0 RADON_NOEXCEPT;

	protected:

		FORCEINLINE TListBase()
			: m_allocator(/*Allocator Name?*/)
			  m_node(nullptr),
			  m_size(0)
		{

		}

		FORCEINLINE TListBase(const AllocatorType &allocator)
			: m_allocator(allocator)
			  m_node(nullptr),
			  m_size(0)
		{

		}

		FORCEINLINE ~TListBase()
		{
			Cleanup();
		}

		FORCEINLINE AllocatorType& GetAllocator() RADON_NOEXCEPT
		{
			return m_allocator;
		}

		FORCEINLINE const AllocatorType& GetAllocator() RADON_NOEXCEPT
		{
			return m_allocator;
		}

		FORCEINLINE NodeType* AllocateNode() RADON_NOEXCEPT
		{
			NodeType *pNewNode = ::AllocateNew(allocator);
			if (!pNewNode)
			{
				SPlatformMemory::HandleMemoryShortage(m_allocator);
			}

			return pNewNode;
		}

		FORCEINLINE void FreeNode(NodeType *pNode) RADON_NOEXCEPT
		{
			::Deallocate(pNode);
		}

	protected:
		AllocatorType m_allocator;
		NodeType     *m_node;
		TSize         m_size;
	};

	struct RADON_API SListIterator { };
	template <typename Iterator>
	struct SReverseIterator { };

	template <typename T, typename Allocator, bool bShared = false>
	class TList : TListBase<TListNode, T, Allocator, bShared>
	{
		INHERITS_FROM(TListBase<TListNode, T, Allocator, bShared>);

		typedef TList<T, Allocator, bShared> MyType;

	public:
		typedef typename Super::NodeType                        NodeType;
		typedef typename Super::AllocatorType                   AllocatorType;
		typedef struct SListIterator							IteratorType;
		typedef struct SListIterator						    ConstIteratorType;
		typedef struct SReverseIterator<SListIterator>          ReverseIteratorType;
		typedef TSubset<TList, ElementType, AllocatorType>		SubsetType;

	public:

		TList()
			: Super() { }

		explicit TList(const AllocatorType &allocator)
			: Super(allocator) {  }

		explicit TList(TSize size)
			: Super()
		{
			AllocateNod
			m_node = ::ConstructNew(m_allocator);

			for (; size > 0; --size)
			{
				
			}
		}

		TList(TSize size, const ElementType &value)
		{

		}

		TList(const MyType &other)
		{

		}


		TList(MyType &&other)
		{

		}

		TList(std::initializer_list<ElementType> initList)
		{

		}

		template<typename OtherIterator>
		TList(OtherIterator first, OtherIterator last)
		{

		}

		~TList()
		{

		}

		FORCEINLINE MyType& SetAllocator(const AllocatorType &allocator) RADON_NOEXCEPT
		{
			RADON_ASSERT(m_size == 0 && m_allocator.GetAllocationSize() == 0);

			m_allocator = allocator;

			return *this;
		}

		MyType& operator=(const MyType &other) RADON_NOEXCEPT
		{

		}

		MyType& operator=(MyType &&other) RADON_NOEXCEPT
		{

		}

		MyType& operator=(std::initializer_list<ElementType> initList) RADON_NOEXCEPT
		{

		}

		FORCEINLINE bool IsEmpty() const RADON_NOEXCEPT
		{
			return m_size == 0;
		}

		FORCEINLINE TSize Size() const RADON_NOEXCEPT
		{
			return m_size;
		}

		FORCEINLINE constexpr TSize GetElementSize() const RADON_NOEXCEPT
		{
			return sizeof(ElementType);
		}

		FORCEINLINE TSize GetAllocationSize() const RADON_NOEXCEPT
		{
			return m_allocator.GetAllocationSize();
		}

		FORCEINLINE void Clear() RADON_NOEXCEPT
		{

		}

		void AddFirst(const ElementType &newElement);
		void AddFirst(ElementType &&newElement);
		void AddFirst(IteratorType first, IteratorType last);
		void AddFirst(std::initializer_list<ElementType> initList);
		void AddLast(const ElementType &newElement);
		void AddLast(ElementType &&newElement);
		void AddLast(Iterator first, Iterator last);
		void AddLast(std::initializer_list<ElementType> initList);

		template <class... Args>
		ElementType& AddFirstConstruct(Args &&...args);

		template <class... Args>
		ElementType& AddLastConstruct(Args &&...args);

		ElementType& AddFirstDefaulted();
		void*        AddFirstUninitialized();
		ElementType& AddLastDefaulted();
		void*        AddLastUninitialized();

		void RemoveFirst();
		void RemoveLast();

		template <typename Predicate>
		void RemoveIf(Predicate filter);
		
		void Reverse() RADON_NOEXCEPT;

		ElementType& Front()
		{
			RADON_ASSERT(m_node);

			return *m_node;
		}

		const ElementType& Front() const
		{

		}

		ElementType& Back()
		{

		}

		const ElementType& Back() const
		{

		}

	protected:

		FORCEINLINE void InsertNodes()
		{

		}
	};

	template <typename T, typename Allocator>
	using TSharedList = TList<T, Allocator, true>;
}

#endif