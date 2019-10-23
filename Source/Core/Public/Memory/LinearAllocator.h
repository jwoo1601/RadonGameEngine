#ifndef RADON_LINEAR_ALLOCATOR_H
#define RADON_LINEAR_ALLOCATOR_H

#include "RadonCore.h"

#include "Allocator.h"

namespace Radon::Memory
{
	class RADON_API XLinearAllocator : public XBaseAllocator
	{
		INHERITS_FROM(XBaseAllocator)

	public:
		
		/* VLinearAllocator Interface */
		XLinearAllocator();
		XLinearAllocator(const SAllocatorInitializer &initializer);
		virtual ~XLinearAllocator();

		virtual void Clear();

		/* VBaseAllocator Interface */
#if RADON_ENABLE_MEMORY_PROFILE
		virtual void PrintMemorySnapshot(XOutputStream &stream) const override;
#endif

		/* IAllocator Interface */
		virtual void* Allocate(TSize size, uint8 alignment, TIndex offset, int32 flag) override;
		virtual void Deallocate(void *ptr) override;

	protected:
		void *m_pCurrent;
	};
}

#endif