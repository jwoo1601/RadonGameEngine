// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_WINDOWS_H
#define RADON_WINDOWS_H

#include "PlatformBase.h"
#include "RadonConfig.h"

#define RADON_PLATFORM_WINDOWS						1
#define RADON_PLATFORM_MAC                          0
#define RADON_PLATFORM_LINUX                        0

#define RADON_PLATFORM_DESKTOP						1
#define RADON_PLATFORM_CONSOLE						0
#define RADON_PLATFORM_MOBILE						0

#define RADON_PLATFORM_SUPPORTS_SIMD				1
#define RADON_PLATFORM_SUPPORTS_SSE2				1
#define RADON_PLATFORM_SUPPORTS_NEON				0

#define RADON_PLATFORM_SUPPORTS_POSIX               0

// Determines Endianness
// Note: We can safely assume that no windows running on desktop support big endian
#define RADON_PLATFORM_TYPE_LITTLE_ENDIAN           1
#define RADON_PLATFORM_TYPE_BIG_ENDIAN              0

// String Encoding Type Used for wchar_t (wide characters)
#define RADON_PLATFORM_SYSTEM_ENCODING              "UTF-16LE"

// Windows Unicode Setup
#define RADON_PLATFORM_SUPPORTS_UNICODE             1
#include "RadonUnicodeSetup.h"

// Forces <Windows.h> to enable/disable unicode
#ifndef _UNICODE
	#define _UNICODE                                RADON_UNICODE
#elif _UNICODE != RADON_UNICODE
	#undef  _UNICODE
	#define _UNICODE                                RADON_UNICODE
#endif

// Forces C Runtime to enable/disable unicode
#ifndef UNICODE
	#define UNICODE                                 RADON_UNICODE
#elif   UNICODE != RADON_UNICODE
	#undef  UNICODE
	#define UNICODE                                 RADON_UNICODE
#endif

namespace Radon
{
	struct RADON_INTERNAL SPlatformWindows : public SPlatformBase
	{
		static void OnPreSetup()
		{

		}

		static void Setup()
		{

		}

		static void OnPostSetup()
		{

		}

		static void OnPreCleanup()
		{

		}

		static void Cleanup()
		{

		}
	};
}

#endif