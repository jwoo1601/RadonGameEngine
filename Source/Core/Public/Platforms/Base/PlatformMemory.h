// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_PLATFORM_MEMORY_H
#define RADON_PLATFORM_MEMORY_H

#include <cstdlib>
#include <cstring>

#include "PlatformMinimal.h"

namespace Radon
{
	struct RADON_API SPlatformMemoryBase
	{
		FORCEINLINE static void* Malloc(TSize size)
		{
			return ::malloc(size);
		}

		FORCEINLINE static void* Calloc(TSize count, TSize size)
		{
			return ::calloc(count, size);
		}

		FORCEINLINE static void* Realloc(void *ptr, TSize size)
		{
			return ::realloc(ptr, size);
		}

		FORCEINLINE static void Free(void *ptr)
		{
			::free(ptr);
		}

		FORCEINLINE static const void* Memchr(const void *ptr, int32 value, TSize count)
		{
			return ::memchr(ptr, value, count);
		}

		FORCEINLINE static int Memcmp(const void *ptr1, const void *ptr2, TSize count)
		{
			return ::memcmp(ptr1, ptr2, count);
		}

		FORCEINLINE static void* Memcpy(void *destPtr, const void *srcPtr, TSize count)
		{
			return ::memcpy(destPtr, srcPtr, count);
		}

		FORCEINLINE static void* Memmove(void *destPtr, const void *srcPtr, TSize count)
		{
			return ::memmove(destPtr, srcPtr, count);
		}

		FORCEINLINE static void* Memset(void *ptr, int32 value, TSize count)
		{
			return ::memset(ptr, value, count);
		}
	};
}

#endif