// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_STATIC_CONFIG_H
#define RADON_STATIC_CONFIG_H

#include "RadonCoreMinimal.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

#include "StaticConverter.h"

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