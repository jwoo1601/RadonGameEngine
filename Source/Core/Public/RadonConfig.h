// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_CONFIG_H
#define RADON_CONFIG_H

#include "StaticConverter.h"

#define RADON_VERSION			 100

namespace Radon::Config
{
	struct SRadonConfig
	{
		constexpr int32 GetVersion()
		{
			return RADON_VERSION;
		}

		constexpr auto GetVersionString()
			-> decltype(VersionString)
		{
			return VersionString;
		}

	private:
		static constexpr auto VersionString = Static::StaticItoa32<RADON_VERSION>();
	};
}

#ifndef RADON_DEBUG
	#if defined(_DEBUG)
		#define RADON_DEBUG						1
	#else
		#define RADON_DEBUG						0
	#endif
#endif

#ifndef RADON_RELEASE
	#if defined(NDEBUG)
		#define RADON_RELEASE					1
	#else
		#define RADON_RELEASE					0
	#endif
#endif


#ifndef RADON_ENABLE_MEMORY_PROFILE
	#define RADON_ENABLE_MEMORY_PROFILE			1
#endif

#ifndef RADON_ENABLE_ASSERTION
	#define RADON_ENABLE_ASSERTION				1
	#include "RadonAssert.h"
#endif

#endif