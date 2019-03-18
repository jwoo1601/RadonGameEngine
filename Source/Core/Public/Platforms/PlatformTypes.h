// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_PLATFORM_TYPES_H
#define RADON_PLATFORM_TYPES_H

#ifdef RADON_PLATFORM_WINDOWS
	#include "PlatformWindowsTypes.h"

#elif RADON_PLATFORM_MAC
	#include "PlatformMacTypes.h"

#elif RADON_PLATFORM_LINUX
	#include "PlatformLinuxTypes.h"

#else
	#include "PlatformBaseTypes.h"

#endif

namespace Radon
{
#ifdef RADON_PLATFORM_WINDOWS
	typedef SPlatformTypesWindows SPlatformTypes;

#elif RADON_PLATFORM_MAC
	typedef SPlatformTypesMac SPlatformTypes;

#elif RADON_PLATFORM_LINUX
	typedef SPlatformTypesLinux SPlatformTypes;

#else
	typedef SPlatformTypesBase SPlatformTypes;

#endif

	typedef SPlatformTypes::uint8			uint8;
	typedef SPlatformTypes::uint16			uint16;
	typedef SPlatformTypes::uint32			uint32;
	typedef SPlatformTypes::uint64			uint64;

	typedef SPlatformTypes::TSize			TSize;
	typedef SPlatformTypes::TIndex			TIndex;

	typedef SPlatformTypes::int8			int8;
	typedef SPlatformTypes::int16			int16;
	typedef SPlatformTypes::int32			int32;
	typedef SPlatformTypes::int64			int64;

	typedef SPlatformTypes::IntPtr			IntPtr;
	typedef SPlatformTypes::UIntPtr			UIntPtr;
	typedef SPlatformTypes::PtrDiff			PtrDiff;

	typedef SPlatformTypes::WChar			WChar;
	typedef SPlatformTypes::char8			char8;
	typedef SPlatformTypes::char16			char16;
	typedef SPlatformTypes::char32			char32;
	typedef SPlatformTypes::TChar			TChar;
}

#endif