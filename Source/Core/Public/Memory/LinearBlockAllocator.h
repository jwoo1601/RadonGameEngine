#pragma once

#include "RadonCore.h"

#include "Memory.hpp"
#include "LinearAllocator.h"

namespace Radon::Memory
{
	struct RADON_API SMemBlock
	{
		void *m_startPtr;
		SMemBlock *m_prevBlock;
		size_t m_size;
		size_t m_usedMemory;
	};

	class RADON_API XLinearBlockAllocator : public XLinearAllocator
	{
		INHERITS_FROM(XLinearAllocator)

	public:

		XLinearBlockAllocator(IAllocator &blockAlloc,
							  size_t blockSize,
							  uint8 blockAlignment) :
			Super(nullptr, 1),
			m_blockAlloc(blockAlloc),
			m_currentBlock(nullptr),
			m_blockSize(blockSize),
			m_blockAlignment(blockAlignment)
		{
			m_totalMemorySize = 0;
		}

		virtual ~XLinearBlockAllocator()
		{

		}

		virtual void Clear() override
		{
			m_usedMemorySize = 0;
			m_blockSize = 0;
			m_numAllocations = 0;
			m_pBase = nullptr;
			m_pCurrent = nullptr;
			m_currentBlock = nullptr;
		}

		virtual void* Allocate(size_t size, uint8 alignment, TIndex offset = 0, int32 flag = 0) override
		{
			RADON_ASSERT(size != 0 && alignment != 0);

			if (m_currentBlock == nullptr)
			{
				AllocateNewBlock(size, alignment);
			}

			uint8 padding = GetForwardAlignmentPadding(m_pCurrent, alignment, offset);

			if (m_currentBlock->m_usedMemory + offset + padding + size > m_currentBlock->m_size)
			{
				AllocateNewBlock(size, alignment);
				padding = GetForwardAlignmentPadding(m_pCurrent, alignment, offset);
			}

			void *pAligned = AddPointer(m_pCurrent, padding);
			size_t allocationSize = padding + size;

			m_pCurrent = AddPointer(m_pCurrent, allocationSize);
			m_currentBlock->m_usedMemory += allocationSize;
			m_usedMemorySize += allocationSize;

			return pAligned;
		}

	protected:

		bool AllocateNewBlock(size_t size, uint8 alignment)
		{
			size_t currentblockSize = size + alignment + sizeof(SMemBlock) + alignof(SMemBlock);
			size_t numBlocks = currentblockSize % m_blockSize == 0 ? currentblockSize / m_blockSize : currentblockSize / m_blockSize + 1;
			size_t newBlockSize = numBlocks * m_blockSize;

			void *newBlockPtr = m_blockAlloc.Allocate(newBlockSize, m_blockAlignment);
			if (!newBlockPtr)
			{
				return false;
			}

			uint8 newBlockPadding = GetForwardAlignmentPadding(newBlockPtr, alignof(SMemBlock));
			SMemBlock *newMemBlockPtr = (SMemBlock*)AddPointer(newBlockPtr, newBlockPadding);
			newMemBlockPtr->m_startPtr = newBlockPtr;
			newMemBlockPtr->m_prevBlock = m_currentBlock;
			newMemBlockPtr->m_size = newBlockSize;
			newMemBlockPtr->m_usedMemory = sizeof(SMemBlock) + newBlockPadding;

			if (m_currentBlock)
			{
				m_usedMemorySize += m_currentBlock->m_size - m_currentBlock->m_usedMemory;
			}

			m_usedMemorySize += newMemBlockPtr->m_usedMemory;

			m_currentBlock = newMemBlockPtr;
			m_pCurrent = m_currentBlock + 1;

			m_totalMemorySize += newBlockSize;

			return true;
		}

	private:
		IAllocator		&m_blockAlloc;
		SMemBlock		*m_currentBlock;
		size_t			 m_blockSize;
		size_t			 m_blockAlignment;
	};
}