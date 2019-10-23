// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_DEBUG_H
#define RADON_DEBUG_H

#include "RadonPlatform.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

#include "RadonConfig.h"

#if RADON_DEBUG
	#if RADON_PLATFORM_WINDOWS
		#include <debugapi.h>
		#define RADON_IS_DEBUGGER_PRESENT()                     IsDebuggerPresent()
		#define RADON_DEBUG_LOG(msg, ...)                       OutputDebugString(msg)
	#elif RADON_PLATFORM_LINUX
		#define RADON_LOG_DEBUG_MESSAGE(msg)                    syslog(msg)
	#endif

	#if RADON_COMPILER_MSVC
		#include <intrin.h>
		#define RADON_DEBUG_BREAK()                             __debugbreak()
	#endif

	#ifndef RADON_DEBUG_BREAK
		#if defined(__i386__) || defined(__x86_64__)
			#define RADON_DEBUG_BREAK()                         __asm__("int $0x03")
		#elif defined(__aarch64__) && defined(__APPLE__)
			#define RADON_DEBUG_BREAK()                         __builtin_trap()
		#elif defined(__aarch64__)
			#define RADON_DEBUG_BREAK()                         __asm__("brk 200")
		#elif defined(__arm__)
			#define RADON_DEBUG_BREAK()                         __asm__("BKPT 200")
		#elif defined(__powerpc__)
			#define RADON_DEBUG_BREAK()                         __asm__(".long 0")
		#else
			#include <signal.h>
			#define RADON_DEBUG_BREAK() raise(SIGTRAP)
		#endif
	#endif
#endif

#endif