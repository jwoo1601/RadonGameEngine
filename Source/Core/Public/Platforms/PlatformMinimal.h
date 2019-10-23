// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_PLATFORM_MINIMAL_H
#define RADON_PLATFORM_MINIMAL_H

#include "RadonCompiler.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

#if defined(_WIN32)
	#include "RadonWindows.h"
#elif defined (__APPLE__)
	#include "RadonMac.h"
#elif defined(__linux__) && !defined(__ANDROID__)
	#include "RadonLinux.h"
#elif defined(__ANDROID__)
	#include "RadonAndroid.h"
#else
	#error Compilation on this platform is currently not supported
#endif

#ifndef RADON_PLATFORM_TYPES_H
	#ifdef RADON_PLATFORM_WINDOWS
		#include "WindowsTypes.h"
	#elif RADON_PLATFORM_MAC
		#include "MacTypes.h"
	#elif RADON_PLATFORM_LINUX
		#include "LinuxTypes.h"
	#elif RADON_PLATFORM_ANDROID
		#include "AndroidTypes.h"
	#else
		#include "PlatformTypes.h"
	#endif
	
	namespace Radon
	{
	#ifdef RADON_PLATFORM_WINDOWS
		typedef SPlatformTypesWindows           SPlatformTypes;
	#elif RADON_PLATFORM_MAC
		typedef SPlatformTypesMac               SPlatformTypes;
	#elif RADON_PLATFORM_LINUX
		typedef SPlatformTypesLinux             SPlatformTypes;
	#elif RADON_PLATFORM_ANDROID
		typedef SPlatformTypesAndroid           SPlatformTypes;
	#else
		typedef SPlatformTypesBase              SPlatformTypes;
	#endif
	
		typedef SPlatformTypes::uint8			uint8;
		typedef SPlatformTypes::uint16			uint16;
		typedef SPlatformTypes::uint32			uint32;
		typedef SPlatformTypes::uint64			uint64;
	
		typedef SPlatformTypes::TSize			TSize;
		typedef SPlatformTypes::TIndex			TIndex;
		typedef SPlatformTypes::TAlign          TAlign;
	
		typedef SPlatformTypes::int8			int8;
		typedef SPlatformTypes::int16			int16;
		typedef SPlatformTypes::int32			int32;
		typedef SPlatformTypes::int64			int64;
	
		typedef SPlatformTypes::IntPtr			IntPtr;
		typedef SPlatformTypes::UIntPtr			UIntPtr;
		typedef SPlatformTypes::PtrDiff			PtrDiff;
	
		typedef SPlatformTypes::ANSIChar        ANSIChar;
		typedef SPlatformTypes::WChar			WChar;
		typedef SPlatformTypes::Char8			Char8;
		typedef SPlatformTypes::Char16			Char16;
		typedef SPlatformTypes::Char32			Char32;
		typedef SPlatformTypes::TChar			TChar;
	}
#endif

#endif