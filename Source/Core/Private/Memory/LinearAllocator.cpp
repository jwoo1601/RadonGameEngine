#include "LinearAllocator.h"

#include "Memory.hpp"

namespace Radon::Memory
{
	VLinearAllocator::VLinearAllocator() { }

	VLinearAllocator::VLinearAllocator(const SAllocatorInitializer &initializer)
		: Super(initializer)
	{
		m_currentPos = m_pBase;
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

#if RADON_ENABLE_MEMORY_PROFILE
	void VLinearAllocator::PrintMemoryDump() const
	{
		printf(
				"base:                        %p\n"
				"currentPos:                  %p\n"
				"totalMemorySize:             %d bytes\n"
				"usedMemorySize:              %d bytes\n"
				"availableMemorySize:         %d bytes\n"
				"numAllocations:              %d\n",
				m_pBase,
				m_currentPos,
				m_totalMemorySize,
				m_usedMemorySize,
				GetAvailableMemorySize(),
				m_numAllocations
			);
	}
#endif

	void* VLinearAllocator::Allocate(size_t size, uint8 alignment, TIndex offset, int32 flag)
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