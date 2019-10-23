// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_PLATFORM_H
#define RADON_PLATFORM_H

#include "PlatformMinimal.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

#ifdef RADON_PLATFORM_WINDOWS
	#include "WindowsString.h"
	#include "WindowsMemory.h"
	#include "WindowsThreads.h"
	#include "WindowsMutex.h"
	#include "WindowsAtomics.h"
#elif RADON_PLATFORM_MAC
	#include "MacString.h"
	#include "MacMemory.h"
	#include "MacThreads.h"
	#include "MacMutex.h"
	#include "MacAtomics.h"
#elif RADON_PLATFORM_LINUX
	#include "LinuxString.h"
	#include "LinuxMemory.h"
	#include "LinuxThreads.h"
	#include "LinuxMutex.h"
	#include "LinuxAtomics.h"
#else
	#include "PlatformString.h"
	#include "PlatformMemory.h"
	#include "PlatformThreads.h"
	#include "PlatformMutex.h"
	#include "PlatformAtomics.h"
#endif

namespace Radon
{
#ifdef RADON_PLATFORM_WINDOWS
	typedef SPlatformStringWindows          SPlatformString;
	typedef SPlatformMemoryWindows          SPlatformMemory;
	typedef SPlatformThreadsWindows         SPlatformThreads;
	typedef SPlatformMutexWindows           SPlatformMutex;
	typedef SPlatformAtomicsWindows         SPlatformAtomics;

#elif RADON_PLATFORM_MAC
	typedef SPlatformStringMac              SPlatformString;
	typedef SPlatformMemoryMac              SPlatformMemory;
	typedef SPlatformThreadsMac             SPlatformThreads;
	typedef SPlatformMutexMac               SPlatformMutex;
	typedef SPlatformAtomicsMac             SPlatformAtomics;

#elif RADON_PLATFORM_LINUX
	typedef SPlatformStringLinux            SPlatformString;
	typedef SPlatformMemoryLinux            SPlatformMemory;
	typedef SPlatformThreadsLinux           SPlatformThreads;
	typedef SPlatformMutexLinux             SPlatformMutex;
	typedef SPlatformAtomicsLinux           SPlatformAtomics;

#else
	typedef SPlatformStringBase             SPlatformString;
	typedef SPlatformMemoryBase             SPlatformMemory;
	typedef SPlatformThreadsBase            SPlatformThreads;
	typedef SPlatformMutexBase              SPlatformMutex;
	typedef SPlatformAtomicsBase            SPlatformAtomics;

#endif
}

#endif