#include "Allocator.h"

#include "RadonAssert.h"

namespace Radon::Memory
{
	// VDefaultAllocator
	void* XDefaultAllocator::Allocate(size_t size, uint8 alignment, TIndex offset, int32 flag)
	{
		return malloc(size);
	}

	void XDefaultAllocator::Deallocate(void *ptr)
	{
		free(ptr);
	}

	// SAllocatorInitializer
	SAllocatorInitializer::SAllocatorInitializer() { }

	SAllocatorInitializer::SAllocatorInitializer(void *pBase, TSize capacity, TSize reservedSize)
		: m_pBase(pBase),
		  m_capacity(capacity),
		  m_reservedSize(reservedSize) { }

#if RADON_ENABLE_MEMORY_PROFILE
	SAllocatorInitializer::SAllocatorInitializer(SName profileName, void *pBase, TSize capacity, TSize reservedSize)
		: SAllocatorInitializer(pBase, capacity, reservedSize)
	{
		m_profileName = profileName;
	}
#endif

	// VBaseAllocator
	XBaseAllocator::XBaseAllocator() { }

	XBaseAllocator::XBaseAllocator(const SAllocatorInitializer &initializer)
	{
		m_pBase = initializer.GetBase();
		m_totalMemorySize = initializer.GetCapacity();
		m_usedMemorySize = initializer.GetReservedSize();
		m_numAllocations = 0;
#if RADON_ENABLE_MEMORY_PROFILE
		m_profileName = initializer.GetProfileName();
#endif
	}

	XBaseAllocator::~XBaseAllocator()
	{
		RADON_ASSERT(m_numAllocations == 0 && m_usedMemory == 0)
	}

#if RADON_ENABLE_MEMORY_PROFILE
	void XBaseAllocator::PrintMemorySnapshot(XOutputStream &stream) const
	{

	}
#endif
}