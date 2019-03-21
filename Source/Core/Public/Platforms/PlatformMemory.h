// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_PLATFORM_MEMORY_H
#define RADON_PLATFORM_MEMORY_H

#if RADON_PLATFORM_WINDOWS
	#include "PlatformWindowsMemory.h"
#elif RADON_PLATFORM_MAC
	#include "PlatformMacMemory.h"
#elif RADON_PLATFORM_LINUX
	#include "PlatformLinuxMemory.h"
#else
	#include "PlatformBaseMemory.h"
#endif

namespace Radon
{
#ifdef RADON_PLATFORM_WINDOWS
	typedef SPlatformMemoryWindows SPlatformMemory;

#elif RADON_PLATFORM_MAC
	typedef SPlatformMemoryMac SPlatformMemory;

#elif RADON_PLATFORM_LINUX
	typedef SPlatformMemoryLinux SPlatformMemory;

#else
	typedef SPlatformMemoryBase SPlatformMemory;

#endif
}

#endif