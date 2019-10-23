// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_ASSERT_H
#define RADON_ASSERT_H

#include <cassert>

#include "RadonPlatform.h"

#if RADON_COMPILER_MSVC
	#include <crtdbg.h>
#elif RADON_COMPILER_CLANG
#elif RADON_COMPILER_GCC
#else
#endif

#define RADON_ASSERT(expr)

#define RADON_ASSERT_MSG(expr, msg)

#define RADON_DEBUG_BREAKPOINT()

#if RADON_COMPILER_CLANG || RADON_COMPILER_GCC
	#define LIKELY(expression)		__builtin_expect(!!(expression), 1)
#else
	#define LIKELY(expression)		(!!(expression))
#endif

#if defined NDEBUG
	#define RADON_CASSERT(expression) (void)0
#else
	#define RADON_CASSERT(expression) \
		( LIKELY(expression)? (void)0 : [] { assert(!#expression); }() )
#endif

#endif