// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_COMPILER_CLANG_H
#define RADON_COMPILER_CLANG_H

#include "CompilerBase.h"

#define __clang_minimal_version__                            (__clang_major__ * 100 + \
                                                              __clang_minor__)

#define __clang_full_version__                              (__clang_minimal_version__ * 100 + \
                                                             __clang_patchlevel__)

#define RADON_SUPPORTED_COMPILER							1

#define RADON_COMPILER_MSVC									0
#define RADON_COMPILER_CLANG								1
#define RADON_COMPILER_GCC									0
#define RADON_COMPILER_MINIMAL_VERSION						__clang_minimal_version__
#define RADON_COMPILER_VERSION                              __clang_full_version__
// #define RADON_COMPILER_VERSION_STRING					__clang_version__

#define RADON_COMPILER_SUPPORTS_PRAGMA_ONCE                 1

// clang version >= 3.3
#if RADON_COMPILER_MINIMAL_VERSION >= 303
	#define RADON_COMPILER_SUPPORTS_CPP11					1
#else
	#define RADON_COMPILER_SUPPORTS_CPP11					0
#endif

// clang version >= 3.4
#if RADON_COMPILER_MINIMAL_VERSION >= 304
	#define RADON_COMPILER_SUPPORTS_CPP14					1
#else
	#define RADON_COMPILER_SUPPORTS_CPP14					0
#endif

// clang version >= 7.0
#if RADON_COMPILER_MINIMAL_VERSION >= 700
	#define RADON_COMPILER_SUPPORTS_CPP17					1
#else
	#define RADON_COMPILER_SUPPORTS_CPP17					0
#endif

// Todo: define RADON_INTERNAL in a proper manner (refer to CompilerGCC.h for details)

#define RADON_INTERNAL

#ifdef RADON_CORE
	#if __has_declspec_attribute(dllexport)
		#define RADON_API									__declspec(dllexport)
	#else
		#if __has_attribute(dllexport)
			#define RADON_API								__attribute__(dllexport)
		#else
			#define RADON_API
		#endif
	#endif
#else
	#if __has_declspec_attribute(dllimport)
		#define RADON_API									__declspec(dllimport)
	#else
		#if __has_attribute(dllimport)
			#define RADON_API								__attribute__(dllimport)
		#else
			#define RADON_API									
		#endif
	#endif
#endif

#if __has_attribute(always_inline)
	#define FORCEINLINE										__attribute__((always_inline))
#else
	#define FORCEINLINE										inline
#endif

#if __has_attribute(noinline)
	#define NOINLINE										__attribute__((noinline))
#else
	#define NOINLINE										
#endif

#if __has_attribute(noreturn)
	#define NORETURN										__attribute__((noreturn))
#else
	#define NORETURN									
#endif

#if __has_c_attribute(deprecated)
	#define RADON_DEPRECATED(x)								[[deprecated(x)]]
#else
/*	#if __has_attribute(deprecated)
		#define RADON_DEPRECATED							__attribute__((deprecated))
	#else
		#define RADON_DEPRECATED
	#endif */

	#if __has_extension(attribute_deprecated_with_message)
		#define RADON_DEPRECATED(x)						    __attribute__((deprecated(x)))
	#else
		#define RADON_DEPRECATED(x)								
	#endif
#endif

#if __has_declspec_attribute(novtable)
	#define	NOVTABLE										__declspec(novtable)
#else
	#define	NOVTABLE										
#endif

#if __has_feature(cxx_alignof)
	#define RADON_COMPILER_SUPPORTS_ALIGNOF					1
	#define RADON_ALIGNOF(x)								alignof(x)
#else
	#define RADON_COMPILER_SUPPORTS_ALIGNOF					0
	#define RADON_ALIGNOF(x)								_RADON_ALIGNOF(x)
#endif

#if __has_feature(cxx_alignas)
	#define RADON_COMPILER_SUPPORTS_ALIGNAS					1
	#define RADON_ALIGNAS(x)								alignas(x)
#else
	#define RADON_COMPILER_SUPPORTS_ALIGNAS					0
	#define RADON_ALIGNAS(x)								__attribute__((aligned(x)))
#endif

#if __has_feature(cxx_constexpr)
	#define RADON_COMPILER_SUPPORTS_CONSTEXPR				1
	#define RADON_CONSTEXPR									constexpr
#else
	#define RADON_COMPILER_SUPPORTS_CONSTEXPR				0
	#define RADON_CONSTEXPR									const
#endif

#if __has_feature(cxx_deleted_functions)
	#define RADON_COMPILER_SUPPORTS_DELETED_FUNCTIONS		1
	#define RADON_DELETE_FUNCTION(x)						x=delete
#else
	#define RADON_COMPILER_SUPPORTS_DELETED_FUNCTIONS		0
	#define RADON_DELETE_FUNCTION(x)						
#endif

#if __has_feature(cxx_defaulted_functions)
	#define RADON_COMPILER_SUPPORTS_DEFAULTED_FUNCTIONS		1
	#define RADON_DEFAULT_FUNCTION(x)						x=default
#else
	#define RADON_COMPILER_SUPPORTS_DEFAULTED_FUNCTIONS		0
	#define RADON_DEFAULT_FUNCTION(x)						
#endif

#if __has_feature(cxx_noexcept)
	#define RADON_COMPILER_SUPPORTS_NOEXCEPT				1
	#define RADON_NOEXCEPT									noexcept
#else
	#define RADON_COMPILER_SUPPORTS_NOEXCEPT				0
	#define RADON_NOEXCEPT									__attribute__((nothrow))
#endif

#if __has_feature(cxx_reference_qualified_functions)
	#define RADON_COMPILER_SUPPORTS_REF_QUALIFIERS			1
	#define RADON_REF_QUALIFIER(x)							x
#else
	#define RADON_COMPILER_SUPPORTS_REF_QUALIFIERS			0
	#define RADON_REF_QUALIFIER(x)							
#endif

#if __has_feature(cxx_thread_local)
	#define RADON_COMPILER_SUPPORTS_THREAD_LOCAL			1
	#define RADON_THREAD_LOCAL								thread_local
#else
	#define RADON_COMPILER_SUPPORTS_THREAD_LOCAL			0
	#define RADON_THREAD_LOCAL								//__attribute__((thread))
#endif

// clang version >= 3.9
#if RADON_COMPILER_MINIMAL_VERSION >= 309
	#define CONSTEXPR_IF(x)									if constexpr(x)
#else
	#define CONSTEXPR_IF(x)									if (x)
#endif

#if __has_c_attribute(fallthrough)
	#define RADON_FALLTHROUGH								[[fallthrough]]
#else
	#define RADON_FALLTHROUGH
#endif

#if __has_c_attribute(nodiscard)
	#define RADON_NODISCARD									[[nodiscard]]
#else
	#define RADON_NODISCARD									
#endif

#if __has_c_attribute(maybe_unused)
	#define RADON_MAYBE_UNUSED								[[maybe_unused]]
#else
	#define RADON_MAYBE_UNUSED								
#endif

#endif // !RADON_COMPILER_CLANG_H