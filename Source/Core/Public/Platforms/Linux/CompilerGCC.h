// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_COMPILER_GCC_H
#define RADON_COMPILER_GCC_H

#include "CompilerBase.h"

#define __GNUC_MINIMAL_VERSION__                            (__GNUC__ * 100 + \
                                                             __GNUC_MINOR__)

#define __GNUC_VERSION__                                    (__GNUC_MINIMAL_VERSION__ * 100 + \
                                                             __GNUC_PATCHLEVEL__)

#define RADON_SUPPORTED_COMPILER							1

#define RADON_COMPILER_MSVC									0
#define RADON_COMPILER_CLANG								0
#define RADON_COMPILER_GCC									1
#define RADON_COMPILER_MINIMAL_VERSION						__GNUC_MINIMAL_VERSION__
#define RADON_COMPILER_VERSION								__GNUC_VERSION__

#define RADON_COMPILER_SUPPORTS_PRAGMA_ONCE                 1

// GCC Version >= 4.8.1
#if RADON_COMPILER_VERSION >= 40801
	#define RADON_COMPILER_SUPPORTS_CPP11					1
#else
	#define RADON_COMPILER_SUPPORTS_CPP11					0
#endif

// GCC Version >= 5.0
#if RADON_COMPILER_MINIMAL_VERSION >= 500
	#define RADON_COMPILER_SUPPORTS_CPP14					1
#else
	#define RADON_COMPILER_SUPPORTS_CPP14					0
#endif

// GCC Version >= 7.0
#if RADON_COMPILER_MINIMAL_VERSION >= 700
	#define RADON_COMPILER_SUPPORTS_CPP17					1
#else
	#define RADON_COMPILER_SUPPORTS_CPP17					0
#endif

#ifdef __has_attribute
	#define gcc_has_attribute(x)                            __has_attribute(x)
#else
	#define gcc_has_attribute(x)                            0
#endif

#if defined (_WIN32) || defined (__CYGWIN__)
	#if defined (RADON_CORE)
		#define RADON_API                                   __attribute__((dllexport))
	#else
		#define RADON_API                                   __attribute__((dllimport))
	#endif
	#define RADON_INTERNAL
#else
	// GCC Version >= 4.0
	#if RADON_COMPILER_MINIMAL_VERSION >= 400
		#if defined (RADON_CORE) && gcc_has_attribute(visibility)
			#define RADON_API                               __attribute__ ((visibility ("default")))
			#define RADON_INTERNAL                          __attribute__ ((visibility ("hidden")))
		#else
			#define RADON_API
			#define RADON_INTERNAL
		#endif
	#else

	#endif
#endif

#ifndef RADON_API
	#define RADON_API
#endif

#ifndef RADON_INTERNAL
	#define RADON_INTERNAL
#endif

#if gcc_has_attribute(always_inline)
	#define FORCEINLINE									    __attribute__((always_inline))
#else
	#define FORCEINLINE                                     inline
#endif

#if gcc_has_attribute(noinline)
	#define NOINLINE									    __attribute__((noinline))
#else
	#define NOINLINE
#endif

#if gcc_has_attribute(noreturn)
	#define NORETURN									    __attribute__((noreturn))
#else
	#define NORETURN
#endif

#define	NOVTABLE

#if radon_has_attribute(deprecated)
	#define RADON_DEPRECATED(x)							    [[deprecated(x)]]
#else
	#if gcc_has_attribute(deprecated)
		#define RADON_DEPRECATED(x)						    __attribute__((deprecated(x)))
	#else
		#define RADON_DEPRECATED(x)								
	#endif
#endif

#if radon_has_attribute(fallthrough)
	#define RADON_FALLTHROUGH								[[fallthrough]]
#else
	#define RADON_FALLTHROUGH
#endif

#if radon_has_attribute(nodiscard)
	#define RADON_NODISCARD									[[nodiscard]]
#else
	#define RADON_NODISCARD									
#endif

#if radon_has_attribute(maybe_unused)
	#define RADON_MAYBE_UNUSED								[[maybe_unused]]
#else
	#define RADON_MAYBE_UNUSED								
#endif

// GCC Version >= 4.8
#if RADON_COMPILER_MINIMAL_VERSION >= 408
	#define RADON_COMPILER_SUPPORTS_ALIGNOF				    1
	#define RADON_ALIGNOF(x)								alignof(x)
#else
	#define RADON_COMPILER_SUPPORTS_ALIGNOF					0
	#define RADON_ALIGNOF(x)								_RADON_ALIGNOF(x)
#endif

// GCC Version >= 4.8
#if RADON_COMPILER_MINIMAL_VERSION >= 408
	#define RADON_COMPILER_SUPPORTS_ALIGNAS					1
	#define RADON_ALIGNAS(x)								alignas(x)
#else
	#if gcc_has_attribute(aligned)
		#define RADON_COMPILER_SUPPORTS_ALIGNAS				1
		#define RADON_ALIGNAS(x)							__attribute__((aligned(x)))
	#else
		#define RADON_COMPILER_SUPPORTS_ALIGNAS				0
		#define RADON_ALIGNAS(x)
	#endif
#endif

#if __cpp_constexpr >= 200704
	#define RADON_COMPILER_SUPPORTS_CONSTEXPR				1
	#define RADON_CONSTEXPR									constexpr
#else
	#define RADON_COMPILER_SUPPORTS_CONSTEXPR				0
	#define RADON_CONSTEXPR									const
#endif

// GCC Version >= 4.4
#if RADON_COMPILER_MINIMAL_VERSION >= 404
	#define RADON_COMPILER_SUPPORTS_DELETED_FUNCTIONS		1
	#define RADON_DELETE_FUNCTION(x)						x=delete
#else
	#define RADON_COMPILER_SUPPORTS_DELETED_FUNCTIONS		0
	#define RADON_DELETE_FUNCTION(x)						
#endif

// GCC Version >= 4.4
#if RADON_COMPILER_MINIMAL_VERSION >= 404
	#define RADON_COMPILER_SUPPORTS_DEFAULTED_FUNCTIONS		1
	#define RADON_DEFAULT_FUNCTION(x)						x=default
#else
	#define RADON_COMPILER_SUPPORTS_DEFAULTED_FUNCTIONS		0
	#define RADON_DEFAULT_FUNCTION(x)						
#endif

// GCC Version >= 4.6
#if RADON_COMPILER_MINIMAL_VERSION >= 406
	#define RADON_COMPILER_SUPPORTS_NOEXCEPT				1
	#define RADON_NOEXCEPT									noexcept
#else
	#if gcc_has_attribute(nothrow)
		#define RADON_COMPILER_SUPPORTS_NOEXCEPT			1
		#define RADON_NOEXCEPT							    __attribute__((nothrow))
	#else
		#define RADON_COMPILER_SUPPORTS_NOEXCEPT            0
		#define RADON_NOEXCEPT
	#endif
#endif

#if __cpp_ref_qualifiers >= 200710
	#define RADON_COMPILER_SUPPORTS_REF_QUALIFIERS			1
	#define RADON_REF_QUALIFIER(x)							x
#else
	#define RADON_COMPILER_SUPPORTS_REF_QUALIFIERS			0
	#define RADON_REF_QUALIFIER(x)							
#endif

// GCC Version >= 4.8
#if RADON_COMPILER_MINIMAL_VERSION >= 408
	#define RADON_COMPILER_SUPPORTS_THREAD_LOCAL			1
	#define RADON_THREAD_LOCAL								thread_local
#else
	#define RADON_COMPILER_SUPPORTS_THREAD_LOCAL			0
	#define RADON_THREAD_LOCAL								//__attribute__((thread))
#endif

#if __cpp_if_constexpr >= 201606
	#define CONSTEXPR_IF(x)									if constexpr(x)
#else
	#define CONSTEXPR_IF(x)									if (x)
#endif

#endif // !RADON_COMPILER_GCC_H