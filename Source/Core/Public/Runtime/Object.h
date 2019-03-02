#pragma once

#include "RadonCore.h"

namespace Radon
{
	// Superclass of any object managed by the engine
	// NOTE: 
	class RADONCORE_API VObject
	{
	public:

		FORCEINLINE void* operator new(size_t size)
		{
			return VEngine::Get()->Allocate(size);
		}

		FORCEINLINE void* operator new[](size_t size)
		{

		}

		FORCEINLINE void operator delete(void *ptr)
		{
			GObjectAllocator.Deallocate(ptr);
		}
	};
}