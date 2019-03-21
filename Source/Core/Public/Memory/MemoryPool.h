// Copyright 2019 Radon Project All Rights Reserved.

#ifndef RADON_MEMORY_POOL_H
#define RADON_MEMORY_POOL_H

#include "RadonCore.h"

#include "Allocator.h"
#include "MemoryScope.hpp"
#include "LinearAllocator.h"
#include "Memory.hpp"

//	 SET_MEMORY_POOL(GetWorld()->GetMemoryPool());
//	 SET_MEMORY_POOL(WorldMemoryPool);
//	 VObject *objPtr = POOLED_NEW(VCharacter)("David");
//	 VObject *objArr = POOLED_NEW(VCharacter)[5];

#define SET_MEMORY_POOL(poolName) \
auto &___target_memory_pool = poolName;

#define POOLED_NEW(type) \
new(___target_memory_pool.AllocateNew<type>()) type

namespace Radon::Memory
{
	struct SMemoryBlock
	{
		void			*m_startPtr;
		SMemoryBlock	*m_pPrevBlock;
//		size_t			 m_blockSize; // not necessary
		size_t			 m_usedMemorySize;

		FORCEINLINE size_t GetAvailableMemorySize(size_t blockDataSize) const
		{
			return blockDataSize - m_usedMemorySize;
		}
	};

	struct RADONCORE_API SMemoryPoolInitializer
	{
		SMemoryPoolInitializer(void *basePtr, size_t poolSize, size_t blockDataSize) :
			m_pBase(basePtr),
			m_poolSize(poolSize),
			m_blockDataSize(blockDataSize)
		{

		}

		void			*m_pBase;
		size_t			 m_poolSize;
		size_t			 m_blockDataSize;
	};

	// -----------------------------------------------------------------------------------------------------------
	// ||       Metadata      ||              SMemoryBlock             ||              SMemoryBlock             || ...
	// -----------------------------------------------------------------------------------------------------------
	// || Allocator | Padding ||  Header  |          content           ||  Header  |          content           || ...
	// -----------------------------------------------------------------------------------------------------------
	// 
	// -> Align in alignof(Allocator) bytes

	// A: Allocator
	template <typename A, typename = TEnableIf<TIsDerivedFrom<A, VBaseAllocator>>>
	class TMemoryPool
	{
		typedef A AllocatorType;

	public:

		/* Constructors */

		// constructs a new memory pool of size {blockSize} * {maxBlockCount}
		TMemoryPool(size_t blockDataSize, size_t maxBlockCount) :
			TMemoryPool(nullptr, blockDataSize, maxBlockCount)
		{

		}

		// constructs a memory pool starting from {pBase} with size {blockSize} * {maxBlockCount}
		TMemoryPool(void *pBase, size_t blockDataSize, size_t maxBlockCount) :
			m_pAlloc(nullptr),
			m_pBase(pBase),
			m_pCurrentBlock(nullptr),
			m_blockDataSize(blockDataSize),
			m_maxBlockCount(maxBlockCount),
			m_currentBlockCount(0)
		{
			m_blockSize = m_blockDataSize + sizeof(SMemoryBlock) + alignof(SMemoryBlock);
			m_poolSize = m_blockSize * m_maxBlockCount;
		}

		/* Destructors */

		~TMemoryPool()
		{

		}

		/* TMemoryPool Interface */

		virtual bool Initialize()
		{
			// {
			//	 TMemoryScope<VStackAllocator> RenderMemoryScope(&RendererMemoryPool, 1024 * 1024);

			//	 NEW_MEMORY_SCOPE(VLinearAllocator, 1024);
			//	 NEW_POOLED_MEMORY_SCOPE(VLinearAllocator, &RendererMemoryPool, 1024 * 1024);
			//	 RenderParameters *paramsPtr = SCOPED_NEW(RenderParameters(0, 5, 4));

			//	 SET_MEMORY_POOL(WorldMemoryPool);
			//	 VObject *objPtr = POOLED_NEW(VCharacter("David"));
			//	 VObject *objArr = POOLED_NEW(VCharacter)[5];
			// }

			// TMemoryPool<VFreeListAllocator> RendererMemoryPool({ MainMemoryPool.GetBasePtr(), 1024 * 1024 * 100, 1024 });
			// RendererMemoryPool.Initialize();
			// VRenderParameter *paramsPtr = RendererMemoryPool.Allocate();
			// ...
			// RenderMemoryPool.Free(paramsPtr);
			// ASSERT(!mallocPtr, "This MemoryPool was already initialized!");

			if (!m_pBase)
			{
				m_pBase = SPlatformMemory::Malloc(m_blockSize * m_maxBlockCount + sizeof(SMemoryBlock));
			}

			// alloc ctor parameters?
			void *pAllocPaddingStart = IncrementPointer(m_pBase, sizeof(AllocatorType));
			uint8 allocPadding = GetForwardAlignmentPadding(pAllocPaddingStart, alignof(SMemoryBlock));

			m_pAlloc = new(m_pBase) AllocatorType(IncrementPointer(pAllocPaddingStart, allocPadding), m_poolSize - sizeof(AllocatorType));

			/* void *pBlockHeader = IncrementPointer(m_pAlloc->GetBasePtr(), allocPadding);
			uint8 blockHeaderPadding = GetForwardAlignmentPadding(pBlockHeader, alignof(SMemoryBlock));

			m_pCurrentBlock = new(pBlockHeader) SMemoryBlock(IncrementPointer(pBlockHeader, sizeof(SMemoryBlock) + blockHeaderPadding), nullptr, m_blockSize); */
			m_curr
			m_currentBlockCount++;

			return true;
		}

		virtual void Clear()
		{

		}

		TMemoryScope<AllocatorType> NewMemoryScope()
		{
			return TMemoryScope<AllocatorType>(11);
		}

		void* AllocateInternal(size_t size, uint8 alignment)
		{
			void *pNewAllocation = nullptr;

			if (m_currentBlockCount < m_maxBlockCount)
			{
//				uint8 dataPadding = GetForwardAlignmentPadding(m_pCurrentBlock->m_startPtr
				if (!m_pCurrentBlock || m_pCurrentBlock->GetAvailableMemorySize(m_blockDataSize) < size)
				{
					pNewBlock->m_pPrevBlock = m_pCurrentBlock;
					m_pCurrentBlock = pNewBlock;
				}
			}
		}

		template <typename T>
		FORCEINLINE T* AllocateNew()
		{
			// ASSERT(m_pAlloc, "This MemoryPool is not initialized!");
			return Memory::AllocateNew<T>(*m_pAlloc);
		}

		template <typename T>
		FORCEINLINE T* AllocateNewArray(size_t arraySize)
		{
			// ASSERT(m_pAlloc, "This MemoryPool is not initialized!");
			return Memory::AllocateNewArray(*m_pAlloc, arraySize);
		}

		template <typename T>
		FORCEINLINE void Free(T *ptr)
		{
			// ASSERT(m_pAlloc, "This MemoryPool is not initialized!");
			// ASSERTS(ptr, "Cannot free nullptr!");
		}

		template <typename T>
		FORCEINLINE void FreeArray(T *arr)
		{

		}

		FORCEINLINE size_t GetBlockSize() const
		{
			return m_blockSize;
		}

		FORCEINLINE size_t GetBlockDataSize() const
		{
			retur m_blockDataSize;
		}

		FORCEINLINE size_t GetPoolSize() const
		{
			return m_poolSize;
		}

		FORCEINLINE size_t GetMaxBlockCount() const
		{
			return m_maxBlockCount;
		}

		FORCEINLINE size_t GetCurrentBlockCount() const
		{
			return m_currentBlockCount;
		}

	protected:

		virtual SMemoryBlock* CreateNewBlock()
		{
			// assert(m_pAlloc && m_pBase);

			SMemoryBlock *pNewBlock = nullptr;

			if (m_pFreeBlock)
			{
				pNewBlock = m_pFreeBlock;
				m_pFreeBlock = pNewBlock->m_pPrevBlock;
			}

			else
			{
				pNewBlock = new(m_pAlloc->AllocateNew(m_blockSize, alignof(SMemoryBlock))) SMemoryBlock{ m_pAlloc->GetCurrentPos(), nullptr, 0 };

				// check if the block is allocated in the right spot (alloc->currentPos + sizeof(SMemoryBlock))
			}

			return pNewBlock;
		}

		virtual void DestroyBlock(SMemoryBlock *blockPtr)
		{
			// usedMemorySize = 0;
		}

	private:
		AllocatorType	*m_pAlloc;
		void			*m_pBase;
		SMemoryBlock	*m_pCurrentBlock;
		SMemoryBlock	*m_pFreeBlock;
		size_t			 m_blockDataSize;
		size_t			 m_blockSize;
		size_t			 m_poolSize;
		size_t			 m_maxBlockCount;
		size_t			 m_currentBlockCount;
	};

	void PoolTest()
	{
		TMemoryPool<VLinearAllocator> memPool(1024, 16);
		SET_MEMORY_POOL(memPool);

		class TestClass
		{
		public:

			TestClass()
			{

			}

			TestClass(const char *str)
			{

			}
		};

		TestClass *testPtr = POOLED_NEW(TestClass)("hi");
		TestClass *testArr = POOLED_NEW(TestClass)[5];
	}
}

#endif