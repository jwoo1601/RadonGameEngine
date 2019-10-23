// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_WINDOWS_MEMORY_H
#define RADON_WINDOWS_MEMORY_H

#include "PlatformMinimal.h"
#include "PlatformMemory.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

#include <malloc.h>

namespace Radon
{
	struct RADON_API SPlatformMemoryWindows : public SPlatformMemoryBase
	{
		FORCEINLINE TSize MemSize(void *ptr)
		{
			return ::_msize(ptr);
		}

		FORCEINLINE static void* AlignedMalloc(TSize size, TAlign alignment)
		{
			return ::_aligned_malloc(size, alignment);
		}

		FORCEINLINE static void* AlignedOffsetMalloc(TSize size, TAlign alignment, TIndex offset)
		{
			return ::_aligned_offset_malloc(size, alignment, offset);
		}

		FORCEINLINE static void AlignedFree(void *ptr)
		{
			::_aligned_free(ptr);
		}

		FORCEINLINE static void* AlignedRealloc(void *oldPtr, TSize newSize, TAlign alignment)
		{
			return ::_aligned_realloc(oldPtr, newSize, alignment);
		}

		FORCEINLINE static void* AlignedOffsetRealloc(void *oldPtr, TSize newSize, TAlign alignment, TIndex offset)
		{
			return ::_aligned_offset_realloc(oldPtr, newSize, alignment, offset);
		}

		FORCEINLINE static void* AlignedRecalloc(void *oldPtr, TSize newSize, TAlign alignment)
		{
			return ::_aligned_recalloc(oldPtr, newSize, alignment);
		}

		FORCEINLINE static void* AlignedOffsetRecalloc(void *oldPtr, TSize newSize, TAlign alignment, TIndex offset)
		{
			return ::_aligned_offset_recalloc(oldPtr, newSize, alignment, offset);
		}

		FORCEINLINE static TSize AlignedMemSize(void *ptr, TAlign alignment, TIndex offset)
		{
			return ::_aligned_msize(ptr, alignment, offset);
		}
	};
}

#endif