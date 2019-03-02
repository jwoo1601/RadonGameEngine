#pragma once

#include <cstdint>

namespace Radon
{
	// Unsigned Integer Types
	typedef uint8_t uint8;
	typedef uint16_t uint16;
	typedef uint32_t uint32;
	typedef uint64_t uint64;

	// Integer Types
	typedef int8_t int8;
	typedef int16_t int16;
	typedef int32_t int32;
	typedef int64_t int64;

	// Pointer to Integer Types
	typedef intptr_t IntPtr;
	typedef uintptr_t UIntPtr;

	// Character Types
	typedef wchar_t wchar;
	typedef char16_t char16;
	typedef char32_t char32;
	typedef char16_t tchar;			// this is the char type used in the engine
}