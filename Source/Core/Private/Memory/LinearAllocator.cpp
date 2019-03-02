#include "LinearAllocator.h"

#include "Memory.hpp"

namespace Radon::Memory
{
	VLinearAllocator::VLinearAllocator(void *basePtr, size_t totalSize)
		: Super(basePtr, totalSize)
	{
		m_currentPos = m_basePtr;
	}

	VLinearAllocator::~VLinearAllocator()
	{

	}

	void VLinearAllocator::Clear()
	{
		m_currentPos = nullptr;
		m_usedMemorySize = 0;
		m_numAllocations = 0;
	}

	void VLinearAllocator::PrintMemoryDump() const
	{
		printf(
				"basePtr:                     %x\n"
				"currentPos:                  %x\n"
				"totalMemorySize:             %d bytes\n"
				"usedMemorySize:              %d bytes\n"
				"availableMemorySize:         %d bytes\n"
				"numAllocations:              %d\n",
				m_basePtr,
				m_currentPos,
				m_totalMemorySize,
				m_usedMemorySize,
				GetAvailableMemorySize(),
				m_numAllocations
			);
	}

	void* VLinearAllocator::Allocate(size_t size, uint8 alignment)
	{
		void *resultPtr = nullptr;

		if (size != 0 && alignment != 0)
		{
#if MEMORY_PROFILING
			printf("--------- Allocation Count: %d ---------\n", m_numAllocations);
			PrintMemoryDump();
			printf("\n");
#endif
			uint8 padding = GetForwardAlignmentPadding(m_currentPos, alignment);
			if (GetAvailableMemorySize() >= padding + size)
			{
				resultPtr = IncrementPointer(m_currentPos, padding);
#if MEMORY_PROFILING
				printf(
						"alignment:                   %d bytes\n"
						"padding:                     %d bytes\n"
						"size:                        %d bytes\n", alignment, padding, size);
#endif

				m_currentPos = IncrementPointer(resultPtr, size);
				m_usedMemorySize += padding + size;
				m_numAllocations++;
#if MEMORY_PROFILING
				printf("\n");
				PrintMemoryDump();
				printf("\n\n");
#endif
			}
		}

		return resultPtr;
	}
}