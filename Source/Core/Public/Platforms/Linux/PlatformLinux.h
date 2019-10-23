// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_LINUX_H
#define RADON_LINUX_H

#define RADON_PLATFORM_WINDOWS						0
#define RADON_PLATFORM_MAC                          0
#define RADON_PLATFORM_LINUX                        1

#define RADON_PLATFORM_DESKTOP						1
#define RADON_PLATFORM_CONSOLE						0
#define RADON_PLATFORM_MOBILE						0

#define RADON_PLATFORM_SUPPORTS_SIMD				1
#define RADON_PLATFORM_SUPPORTS_SSE2				1
#define RADON_PLATFORM_SUPPORTS_NEON				0

#define RADON_PLATFORM_SUPPORTS_POSIX               1

// Determines Endianness
#include <endian.h>
#if __BYTE_ORDER == __LITTLE_ENDIAN
	#define RADON_PLATFORM_LITTLE_ENDIAN            1
	#define RADON_PLATFORM_BIG_ENDIAN               0
#elif __BYTE_ORDER == __BIG_ENDIAN
	#define RADON_PLATFORM_LITTLE_ENDIAN            0
	#define RADON_PLATFORM_BIG_ENDIAN               1
#else
	#define RADON_PLATFORM_LITTLE_ENDIAN            0
	#define RADON_PLATFORM_BIG_ENDIAN               0
#endif

// String Encoding Type Used for wchar_t (wide characters)
#if RADON_PLATFORM_LITTLE_ENDIAN
	#define RADON_PLATFORM_SYSTEM_ENCODING          "UTF-32LE"
#elif RADON_PLATFORM_BIG_ENDIAN
	#define RADON_PLATFORM_SYSTEM_ENCODING          "UTF-32BE"
#else
	#define RADON_PLATFORM_SYSTEM_ENCODING          "UTF-32"
#endif

#define RADON_PLATFORM_SUPPORTS_UNICODE             1

#endif