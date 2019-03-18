#pragma once

#include "RadonCore.h"

#include "World.h"

namespace Radon
{
	// Superclass of any object managed by the engine
	// NOTE: 
	class RADONCORE_API VObject
	{
	public:

		FORCEINLINE void* operator new(size_t size)
		{
#if ALLOW_MANUAL_OBJECT_CREATION
			return SPlatformMemory::Malloc(size);
#else
			return nullptr;
#endif
		}

		FORCEINLINE void* operator new[](size_t size)
		{
#if ALLOW_MANUAL_OBJECT_CREATION
			return SPlatformMemory::Malloc(size);
#else
			return nullptr;
#endif
		}

		FORCEINLINE void operator delete(void *ptr)
		{
#if ALLOW_MANUAL_OBJECT_CREATION
			SPlatformMemory::Free(ptr);
#endif
		}

		FORCEINLINE void operator delete[](void *arr)
		{
#if ALLOW_MANUAL_OBJECT_CREATION
			SPlatformMemory::Free(arr);
#endif
		}

		virtual VWorld* GetWorld() const;
	};
}