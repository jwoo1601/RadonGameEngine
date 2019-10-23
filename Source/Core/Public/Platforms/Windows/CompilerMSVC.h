// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_COMPILER_MSVC_H
#define RADON_COMPILER_MSVC_H

/*		
 *		MSVC	|	Visual Studio
 *		1600	|		2010
 *		1700	|		2012
 *		1800	|		2013
 *		1900	|		2015
 *		1910	|		2017
 */

#include "CompilerBase.h"

#define RADON_SUPPORTED_COMPILER							1

#define RADON_COMPILER_MSVC									1
#define RADON_COMPILER_CLANG								0
#define RADON_COMPILER_GCC									0
#define RADON_COMPILER_OTHER                                0
#define RADON_COMPILER_MINIMAL_VERSION						_MSC_VER
#define RADON_COMPILER_VERSION								_MSC_FULL_VER

#ifdef RADON_CORE
	#define RADON_API										__declspec(dllexport)
#else
	#define RADON_API										__declspec(dllimport)
#endif

#define RADON_INTERNAL

#define FORCEINLINE											__forceinline
#define NOINLINE											__declspec(noinline)
#define	NOVTABLE											__declspec(novtable)


#if RADON_COMPILER_MINIMAL_VERSION >= 1020
#define RADON_COMPILER_SUPPORTS_PRAGMA_ONCE                 1
#else
#define RADON_COMPILER_SUPPORTS_PRAGMA_ONCE                 0
#endif

#if RADON_COMPILER_MINIMAL_VERSION >= 1800
	#define RADON_COMPILER_SUPPORTS_CPP11					1

	#define RADON_COMPILER_SUPPORTS_DELETED_FUNCTIONS		1
	#define RADON_DELETE_FUNCTION(x)						x=delete

	#define RADON_COMPILER_SUPPORTS_DEFAULTED_FUNCTIONS		1
	#define RADON_DEFAULT_FUNCTION(x)						x=default

#else
	#define RADON_COMPILER_SUPPORTS_DELETED_FUNCTIONS		0
	#define RADON_DELETE_FUNCTION(x)						

	#define RADON_COMPILER_SUPPORTS_DEFAULTED_FUNCTIONS		0
	#define RADON_DEFAULT_FUNCTION(x)
#endif // RADON_COMPILER_MINIMAL_VERSION >= 1800

#if RADON_COMPILER_MINIMAL_VERSION >= 1900
	#define RADON_COMPILER_SUPPORTS_CPP14					1

	#define RADON_COMPILER_SUPPORTS_NOEXCEPT				1
	#define RADON_NOEXCEPT									noexcept

	#define RADON_COMPILER_SUPPORTS_ALIGNOF					1
	#define RADON_ALIGNOF(x)								alignof(x)

	#define RADON_COMPILER_SUPPORTS_ALIGNAS					1
	#define RADON_ALIGNAS(x)								alignas(x)

	#define RADON_COMPILER_SUPPORTS_CONSTEXPR				1
	#define RADON_CONSTEXPR									constexpr

	#define RADON_COMPILER_SUPPORTS_REF_QUALIFIERS			1
	#define RADON_REF_QUALIFIER(x)							x

	#define RADON_DEPRECATED(x)								[[deprecated(x)]]

#else
	#define RADON_COMPILER_SUPPORTS_CPP14					0

	#define RADON_COMPILER_SUPPORTS_NOEXCEPT				0
	#define RADON_NOEXCEPT						

	#define RADON_COMPILER_SUPPORTS_ALIGNOF					0
	#define RADON_ALIGNOF(x)								_RADON_ALIGNOF(x)

	#define RADON_COMPILER_SUPPORTS_ALIGNAS					0
	#define RADON_ALIGNAS(x)								__declspec(align(x))

	#define RADON_COMPILER_SUPPORTS_CONSTEXPR				0
	#define RADON_CONSTEXPR									const

	#define RADON_COMPILER_SUPPORTS_REF_QUALIFIERS			0
	#define RADON_REF_QUALIFIER(x)						

	#define RADON_DEPRECATED(x)								__declspec(deprecated(x))

#endif // RADON_COMPILER_MINIMAL_VERSION >= 1900

#if RADON_COMPILER_MINIMAL_VERSION >= 1910
	#define RADON_FALLTHROUGH								[[fallthrough]]

#else
	#define RADON_FALLTHROUGH								
#endif

#if RADON_COMPILER_MINIMAL_VERSION >= 1911
	#define RADON_NODISCARD									[[nodiscard]]
	#define RADON_MAYBE_UNUSED								[[maybe_unused]]

	#define CONSTEXPR_IF(x)									if constexpr(x)
#else
	#define RADON_NODISCARD									
	#define RADON_MAYBE_UNUSED		

	#define CONSTEXPR_IF(x)									if (x)
#endif

#if RADON_COMPILER_MINIMAL_VERSION >= 1915
	#define RADON_COMPILER_SUPPORTS_CPP17					1

#else
	#define RADON_COMPILER_SUPPORTS_CPP17					0
#endif // RADON_COMPILER_MINIMAL_VERSION >= 1915

#endif // !RADON_COMPILER_MSVC_H