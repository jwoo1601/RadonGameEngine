#ifndef RADON_PLATFORM_CONFIG_H
#define RADON_PLATFORM_CONFIG_H

// Platform Specific Includes and Macros
#if defined(PLATFORM_WINDOWS)
	#include "PlatformWindows.h"
#elif defined(PLATFORM_MAC)
	#include "PlatformMac.h"
#elif defined(PLATFORM_LINUX)
	#include "PlatformLinux.h"
#else
	#error Platform currently not supported
#endif

#endif