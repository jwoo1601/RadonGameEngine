// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_PLATFORM_STRING_H
#define RADON_PLATFORM_STRING_H

#include "PlatformConfig.h"

#pragma warning(disable: 4996)

#if RADON_PLATFORM_WINDOWS
	#include "PlatformWindowsString.h"
#elif RADON_PLATFORM_MAC
	#include "PlatformMacString.h"
#elif RADON_PLATFORM_LINUX
	#include "PlatformLinuxString.h"
#else
	#include "PlatformBaseString.h"
#endif

namespace Radon
{
#ifdef RADON_PLATFORM_WINDOWS
	typedef SPlatformStringWindows SPlatformString;

#elif RADON_PLATFORM_MAC
	typedef SPlatformStringMac SPlatformString;

#elif RADON_PLATFORM_LINUX
	typedef SPlatformStringLinux SPlatformString;

#else
	typedef SPlatformStringBase SPlatformString;

#endif
}

#endif