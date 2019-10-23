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
	template <typename Allocator>
	struct TMemoryBlock
	{
		typedef Allocator AllocatorType;

		AllocatorType    allocator;
		void			*pStart;
		TMemoryBlock	*pAdjacent;
		TSize			 blockSize;
		TSize			 usedMemorySize;

		FORCEINLINE TSize GetAvailableMemorySize() const
		{
			return blockSize - usedMemorySize;
		}
	};

	struct RADON_API SMemoryPoolInitializer
	{
		TSize            blockSize;
		TSize			 initialiBlockCount;
		uint8            bAllowGrowing : 1;
	};

	// -----------------------------------------------------------------------------------------------------------
	// ||       Metadata      ||              SMemoryBlock             ||              SMemoryBlock             || ...
	// -----------------------------------------------------------------------------------------------------------
	// || Allocator | Padding ||  Header  |          content           ||  Header  |          content           || ...
	// -----------------------------------------------------------------------------------------------------------
	// 
	// -> Align in alignof(Allocator) bytes

			// | padding |       MemoryBlock       | padding | MemoryBlock | ...
		//           | header | allocationBody |
		//                    ^
		//             allocator.pBase

	class RADON_API XMemoryManager
	{
		typedef XMemoryManager MyType;

	public:

		virtual void OnPreInitialize();
		virtual void Initialize(TSize perThreadMemoryPoolCount, TSize memoryBlockSize);
		virtual void OnPostInitialize();

		virtual void* RequestLocalAllocation(TSize allocationSize);
		virtual void  RequestLocalDeallocation(void *ptr);

		virtual void* RequestSharedAllocation(TSize allocationSize);
		virtual void  RequestSharedDeallocation(void *ptr);

		template <typename Allocator>
		MyType& MakeLocalMemoryPool(SThreadId tid, SName name, TSize blockSize, TSize blockCount, bool bAllowGrowing);

		template <typename Allocator>
		MyType& MakeSharedMemoryPool(SName name, TSize blockSize, TSize blockCount, bool bAllowGrowing);

		MyType& DeleteLocalMemoryPool(SName name);
		MyType& DeleteSharedMemoryPool(SName name);

		TMemoryPool GetLocalMemoryPool() const;

		MyType& NewSection();

	private:
		XFreeListAllocator m_allocator;
	};

	template <typename Allocator, typename = TEnableIf<TIsDerivedFrom<Allocator, XBaseAllocator>>>
	class TMemoryPool
	{
		//		CLASS_NOT_COPYABLE(TMemoryPool);

	public:
		typedef Allocator                      AllocatorType;
		typedef TMemoryBlock<AllocatorType>    BlockType;
		typedef TMemoryScope<AllocatorType>    ScopeType;

		/* Constructors */
		TMemoryPool(const SMemoryPoolInitializer &initializer, XMemoryManager &manager)
			: m_manager(manager)
		{
			m_blockSize = initializer.blockSize;
			m_blockCount = initializer.initialiBlockCount;
			m_bAllowGrowing = initializer.bAllowGrowing;
		}

		virtual ~TMemoryPool()
		{
			if (m_bInitialized)
			{
				m_manager.ReturnAllocatedMemory(m_allocator.GetBase());
			}
		}

		virtual void Initialize()
		{
			if (!m_bInitialized)
			{
				TSize estimatedSize = EstimateAllocationSize();
				m_pStart = manager.RequestMemoryAllocation(estimatedSize);
				m_pEnd = AddPointer(m_pStart, estimatedSize);

				void *pCurrent = m_pStart;
				for (int i = 0; i < m_blockCount; i++)
				{
					BlockType *pNewBlock = CreateNewBlock(pCurrent);

					if (m_pFreeBlocks)
					{
						// forward list
						m_pFreeBlocks->pAdjacent = pNewBlock;
					}

					m_pFreeBlocks = pNewBlock;
				}

				m_bInitialized = true;
			}
		}

		virtual void Cleanup()
		{
			if (m_bInitialized)
			{

			}
		}

		ScopeType MakeMemoryScope()
		{

		}

		template <typename T>
		FORCEINLINE T* AllocateNew(TIndex offset = 0, int32 flag = 0)
		{
			return DoAllocate(sizeof(T), RADON_ALIGNOF(T), offset, flag);
		}

		template <typename T>
		FORCEINLINE T* AllocateNewArray(TSize arraySize, TIndex offset = 0, int32 flag = 0)
		{
			return DoAllocate(sizeof(T) * arraySize, RADON_ALIGNOF(T), offset, flag);
		}

		template <typename T>
		FORCEINLINE void Free(T *ptr)
		{
			DoFree(ptr);
		}

		template <typename T>
		FORCEINLINE void FreeArray(T *arr)
		{
			DoFree(ptr);
		}

		FORCEINLINE TSize GetBlockSize() const
		{
			return m_blockSize;
		}

		FORCEINLINE TSize GetBlockCount() const
		{
			return m_blockCount;
		}

		FORCEINLINE TSize GetAllocationSize() const
		{
			return static_cast<TSize>(reinterpret_cast<UIntPtr>(m_pEnd) - reinterpret_cast<UIntPtr>(m_pStart));
		}

	protected:

		virtual TSize EstimateAllocationSize() const
		{
			return (m_blockSize + sizeof(BlockType) + RADON_ALIGNOF(BlockType)) * m_blockCount;
		}

		virtual BlockType* CreateNewBlock(void *&pCurrent)
		{
			RADON_ASSERT(pCurrent);

			uint8 padding = GetForwardAlignmentPadding(m_pCurrent, RADON_ALIGNOF(BlockType));
			IncrementPointer(pCurrent, padding);

			BlockType *pNewBlock = new(pCurrent) BlockType;
			pNewBlock->blockSize = m_blockSize;
			pNewBlock->pAdjacent = nullptr;
			pNewBlock->pStart = AddPointer(pNewBlock, sizeof(BlockType));
			pNewBlock->allocator.initialize(pNewBlock->pStart, pNewBlock->blockSize);
			pNewBlock->usedMemorySize = 0;

			pCurrent = AddPointer(pNewBlock->pStart, pNewBlock->blockSize);

			return pNewBlock;
		}

		virtual void* DoAllocate(TSize size, uint8 alignment, TIndex offset, int32 flag)
		{
			RAODN_ASSERT(m_bInitialized);

			void *pAllocation = nullptr;
			TSize minimalAllocationSize = size + offset;

			if (m_blockSize >= minimalAllocationSize)
			{
				if (m_pCurrentBlock->GetAvailableMemorySize() < minimalAllocationSize)
				{
					if (m_pFreeBlocks)
					{
						BlockType *pNewBlock = m_pFreeBlocks;
						m_pFreeBlocks = m_pFreeBlocks->pNext;

						m_pCurrentBlock->pNext
					}
				}

				pAllocation = m_pCurrentBlock->allocator.Allocate(size, alignment, offset, flag);
				uint8 padding = GetForwardAlignmentPadding(pAllocation, alignment, offset); // or m_pCurrentBlock->allocator.GetPadding(pAllocation, alignment, offset);
			}

			return pAllocation;
		}

		virtual void DoFree(void *ptr)
		{
			RADON_ASSERT(m_bInitialized, "MemoryPool must be initialized before allocation");
			RADON_ASSERT(ptr, "nullptr cannot be freed");
			RADON_ASSERT(ptr >= m_pStart && ptr < m_pEnd);

			constexpr auto dd = sizeof(TMemoryPool<XLinearAllocator>);
		}

	private:
		// All the allocations made by this memory pool should be within m_pStart <= ptr < m_pEnd 
		void            *m_pStart;
		void            *m_pEnd;
		XMemoryManager   &m_manager;

		BlockType       *m_pUsedBlocks; // backward list: null <- block <- block...
		BlockType       *m_pFreeBlocks; // forward list: ...block -> block -> null
		TSize			 m_blockSize;
		TSize			 m_blockCount;

		uint8            m_bInitialized : 1;
		// enables dynamic growing of memory pool (this operation has a bit more overhead)
		uint8            m_bAllowGrowing : 1;
	};

	/*	void PoolTest()
		{
			{
				TMemoryScope<VStackAllocator> RenderMemoryScope(&RendererMemoryPool, 1024 * 1024);

				NEW_MEMORY_SCOPE(VLinearAllocator, 1024);
				NEW_POOLED_MEMORY_SCOPE(VLinearAllocator, &RendererMemoryPool, 1024 * 1024);
				RenderParameters *paramsPtr = SCOPED_NEW(RenderParameters(0, 5, 4));

				SET_MEMORY_POOL(WorldMemoryPool);
				VObject *objPtr = POOLED_NEW(VCharacter("David"));
				VObject *objArr = POOLED_NEW(VCharacter)[5];
			}

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
		} */
}

#endif