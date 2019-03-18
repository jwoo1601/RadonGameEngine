// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_PLATFORM_BASE_TYPES_H
#define RADON_PLATFORM_BASE_TYPES_H

#include <cstdint>

namespace Radon
{
	struct SPlatformTypesBase
	{
		// Unsigned Integer Types
		typedef uint8_t			uint8;
		typedef uint16_t		uint16;
		typedef uint32_t		uint32;
		typedef uint64_t		uint64;

		typedef size_t			TSize;
		typedef TSize			TIndex;

		// Integer Types
		typedef int8_t			int8;
		typedef int16_t			int16;
		typedef int32_t			int32;
		typedef int64_t			int64;

		// Pointer Types
		typedef intptr_t		IntPtr;
		typedef uintptr_t		UIntPtr;
		typedef ptrdiff_t		PtrDiff;

		// Character Types
	//	typedef char			char;
		typedef wchar_t			WChar;
		typedef char/*8_t*/		char8;		// This should be char8_t not char
		typedef char16_t		char16;
		typedef char32_t		char32;
		// The only char type used to represent unicode characters in the engine
		typedef WChar			TChar;

		/*
		 * NOTE: TChar should be char8 as Radon Engine encodes characters in UTF-8 when stored into external files;
		 *		however, since currently almost no platforms support char8_t (added in C++20), which is guaranteed to represent characters in UTF-8,
		 *		we use wchar_t, which is a platform-dependent char type (UTF-16LE on Windows, UTF-32 on Mac and Linux),
		 *		as it is widely supported and we can use platform-specific Wide-char to UTF-8 conversion functions.
		 */

		 /*
		  * Disclaimer: the actual type of TChar may vary on each platform! Do not think that TChar will always be wchar_t
		  */
	};
}

#endif