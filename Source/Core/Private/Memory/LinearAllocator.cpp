#include "LinearAllocator.h"

#include "Memory.hpp"

namespace Radon::Memory
{
	XLinearAllocator::XLinearAllocator() { }

	XLinearAllocator::XLinearAllocator(const SAllocatorInitializer &initializer)
		: Super(initializer)
	{
		m_pCurrent = m_pBase;
	}

	XLinearAllocator::~XLinearAllocator()
	{

	}

	void XLinearAllocator::Clear()
	{
		m_pCurrent = nullptr;
		m_usedMemorySize = 0;
		m_numAllocations = 0;
	}

#if RADON_ENABLE_MEMORY_PROFILE
	void XLinearAllocator::PrintMemorySnapshot(XOutputStream &stream) const
	{
		printf(
				"base:                        %p\n"
				"currentPos:                  %p\n"
				"totalMemorySize:             %d bytes\n"
				"usedMemorySize:              %d bytes\n"
				"availableMemorySize:         %d bytes\n"
				"numAllocations:              %d\n",
				m_pBase,
				m_pCurrent,
				m_totalMemorySize,
				m_usedMemorySize,
				GetAvailableMemorySize(),
				m_numAllocations
			);
	}
#endif

	void* XLinearAllocator::Allocate(TSize size, uint8 alignment, TIndex offset, int32 flag)
	{
		void *pResult = nullptr;

		if (size != 0 && alignment != 0)
		{
			uint8 padding = GetForwardAlignmentPadding(m_pCurrent, alignment, offset);
			if (GetAvailableMemorySize() >= padding + size)
			{
				pResult = AddPointer(m_pCurrent, padding);
#if RADON_ENABLE_MEMORY_PROFILE
				printf(
						"alignment:                   %d bytes\n"
						"padding:                     %d bytes\n"
						"size:                        %d bytes\n", alignment, padding, size);
#endif
				m_pCurrent = AddPointer(pResult, size);
				m_usedMemorySize += padding + size;
				m_numAllocations++;
			}
		}

		return pResult;
	}

	void XLinearAllocator::Deallocate(void *ptr)
	{

	}
}