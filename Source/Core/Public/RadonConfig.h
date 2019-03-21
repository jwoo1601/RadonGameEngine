// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_CONFIG_H
#define RADON_CONFIG_H

#include "StaticConverter.h"

#define RADON_VERSION                                100

#ifdef _DEBUG
	#define RADON_DEBUG                              1
#else
	#define RADON_DEBUG                              0
#endif

#ifdef NDEBUG
	#define RADON_RELEASE                            1
#else
	#define RADON_RELEASE                            0
#endif

#if RADON_DEBUG
	#define RADON_ENABLE_MEMORY_PROFILE              1
	#define RADON_ENABLE_ASSERTION                   1
#else
	#define RADON_ENABLE_MEMORY_PROFILE              0
	#define RADON_ENABLE_ASSERTION                   0
#endif


#if RADON_ENABLE_ASSERTION
	#include "RadonAssert.h"
#endif

namespace Radon::Config
{
	struct SRadonConfig
	{
	private:
		static constexpr auto VersionString = Static::Itoa32<RADON_VERSION>();

	public:

		constexpr int32 GetVersion()
		{
			return RADON_VERSION;
		}

		constexpr auto GetVersionString() -> decltype(VersionString)
		{
			return VersionString;
		}
	};
}

#endif