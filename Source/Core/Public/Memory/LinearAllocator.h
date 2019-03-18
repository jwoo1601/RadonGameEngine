#pragma once

#include "RadonCore.h"

#include "Allocator.h"

namespace Radon::Memory
{
	class RADONCORE_API VLinearAllocator : public VBaseAllocator
	{
		INHERITS_FROM(VBaseAllocator)

	public:

		VLinearAllocator(void *basePtr, size_t totalSize);
		virtual ~VLinearAllocator();

		// VLinearAllocator Interface
		virtual void Clear();

		virtual void PrintMemoryDump() const;

		// IAllocator Interface
		virtual void* Allocate(TSize size, uint8 alignment, TIndex offset, int32 flag) override;

		[[deprecated("use of {Deallocate} is prohibited since this is a linear allocator")]]
		virtual void Deallocate(void *ptr) override { }

	protected:
		void *m_currentPos;
	};
}