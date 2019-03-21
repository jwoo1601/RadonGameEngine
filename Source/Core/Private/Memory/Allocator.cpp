#include "Allocator.h"

namespace Radon::Memory
{
	// VDefaultAllocator
	void* VDefaultAllocator::Allocate(size_t size, uint8 alignment, TIndex offset, int32 flag)
	{
		return malloc(size);
	}

	void VDefaultAllocator::Deallocate(void *ptr)
	{
		free(ptr);
	}

	// VBaseAllocator
	VBaseAllocator::VBaseAllocator()
	{

	}

/*	VBaseAllocator::VBaseAllocator(void *basePtr, size_t totalSize)
		: m_basePtr(basePtr),
		  m_totalMemorySize(totalSize),
		  m_usedMemorySize(0),
		  m_numAllocations(0)
	{

	} */

	VBaseAllocator::~VBaseAllocator()
	{
		// Must assert m_numAllocations == 0 && m_usedMemory == 0
	}
}