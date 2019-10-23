#ifndef RADON_STACK_ALLOCATOR_H
#define RADON_STACK_ALLOCATOR_H

#include "RadonCore.h"

#include "LinearAllocator.h"

namespace Radon::Memory
{
	class RADON_API XStackAllocator : public XLinearAllocator
	{
		INHERITS_FROM(XLinearAllocator)

	public:
		typedef void* TMarker;

		/* VStackAllocator Interface */
		XStackAllocator();
		XStackAllocator(const SAllocatorInitializer &initializer);
		virtual ~XStackAllocator();

		TMarker Mark();
		void Rollback(TMarker marker);
	};
}

#endif