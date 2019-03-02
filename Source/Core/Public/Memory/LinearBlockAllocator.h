#pragma once

#include "RadonCore.h"

#include "LinearAllocator.h"

namespace Radon::Memory
{
	struct SMemoryBlock
	{
		void			*m_basePtr;
		SMemoryBlock	*m_prevBlock;
		size_t			 m_blockSize;
		size_t			 m_usedMemorySize;

		FORCEINLINE size_t GetAvailableMemorySize() const
		{
			return m_blockSize - m_usedMemorySize;
		}
	};

	class RADONCORE_API VLinearBlockAllocator : public VLinearAllocator
	{
		INHERITS_FROM(VLinearAllocator)

	public:

		VLinearBlockAllocator(void *basePtr, size_t totalSize);
		VLinearBlockAllocator();
		virtual ~VLinearBlockAllocator();

		virtual void* Allocate(size_t size, uint8 alignment) override;
		virtual void Deallocate(void *ptr) override;

	private:

		IAllocator		*m_blockAlloc;
		SMemoryBlock	*m_currentBlock;
		size_t			 m_blockCount;
		size_t			 m_blockAlignment;
	};
}