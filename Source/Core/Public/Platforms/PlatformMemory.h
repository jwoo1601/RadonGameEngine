// Copyright 2019 Simon Kim All Rights Reserved.

#pragma once

#include <cstdlib>
#include <cstring>

#include "RadonCore.h"

namespace Radon
{
	struct RADONCORE_API SPlatformMemory
	{
		FORCEINLINE static void* Malloc(size_t size)
		{
			return ::malloc(size);
		}

		FORCEINLINE static void* Calloc(size_t count, size_t size)
		{
			return ::calloc(count, size);
		}

		FORCEINLINE static void* Realloc(void *ptr, size_t size)
		{
			return ::realloc(ptr, size);
		}

		FORCEINLINE static void Free(void *ptr)
		{
			::free(ptr);
		}

		FORCEINLINE static const void* Memchr(const void *ptr, int32 value, size_t count)
		{
			return ::memchr(ptr, value, count);
		}

		FORCEINLINE static int Memcmp(const void *ptr1, const void *ptr2, size_t count)
		{
			return ::memcmp(ptr1, ptr2, count);
		}

		FORCEINLINE static void* Memcpy(void *destPtr, const void *srcPtr, size_t count)
		{
			return ::memcpy(destPtr, srcPtr, count);
		}

		FORCEINLINE static void* Memmove(void *destPtr, const void *srcPtr, size_t count)
		{
			return ::memmove(destPtr, srcPtr, count);
		}

		FORCEINLINE static void* Memset(void *ptr, int32 value, size_t count)
		{
			return ::memset(ptr, value, count);
		}
	};
}