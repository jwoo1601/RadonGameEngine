#pragma once

// Platform Specific Includes and Macros
#if defined(PLATFORM_WINDOWS)
#include "PlatformWindows.h"

#define PLATFORM_WINDOWS	1
#define PLATFORM_MAC		0
#define PLATFORM_LINUX		0

#elif defined(PLATFORM_MAC)
#include "PlatformMac.h"

#define PLATFORM_WINDOWS	0
#define PLATFORM_MAC		1
#define PLATFORM_LINUX		0

#elif defined(PLATFORM_LINUX)
#include "PlatformLinux.h"

#define PLATFORM_WINDOWS	0
#define PLATFORM_MAC		0
#define PLATFORM_LINUX		1

#else
#error Platform currently not supported
#endif