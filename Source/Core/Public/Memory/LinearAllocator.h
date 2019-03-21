#pragma once

#include "RadonCore.h"

#include "Allocator.h"

namespace Radon::Memory
{
	class RADON_API VLinearAllocator : public VBaseAllocator
	{
		INHERITS_FROM(VBaseAllocator)

	public:
		
		VLinearAllocator();
		VLinearAllocator(const SAllocatorInitializer &initializer);

		virtual ~VLinearAllocator();

		/* VLinearAllocator Interface */
		virtual void Clear();

#if RADON_ENABLE_MEMORY_PROFILE
		virtual void PrintMemoryDump() const;
#endif

		// IAllocator Interface
		virtual void* Allocate(TSize size, uint8 alignment, TIndex offset, int32 flag) override;

		[[deprecated("use of {Deallocate} is prohibited since this is a linear allocator")]]
		virtual void Deallocate(void *ptr) override { }

	protected:
		void *m_currentPos;
	};
}