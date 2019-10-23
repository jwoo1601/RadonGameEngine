// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_COMPILER_BASE_CONFIG_H
#define RADON_COMPILER_BASE_CONFIG_H

#include "PlatformMinimal.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

#include "CompilerUtils.h"

namespace Radon::Config
{
	using Radon::Utils::TCompilerVersion;

	struct RADON_API SCompilerConfigBase
	{
		typedef TCompilerVersion<0, 0, 0, 0> Version;

		static constexpr bool HasUnicodeSupport()
		{
			return RADON_PLATFORM_SUPPORTS_UNICODE;
		}

		static constexpr char* GetSystemEncoding()
		{
			return RADON_PLATFORM_SYSTEM_ENCODING;
		}

		static constexpr TSize GetWideCharSize()
		{
			return sizeof(WChar);
		}

		static constexpr bool HasCompleteCpp11Support()
		{
			return RADON_COMPILER_SUPPORTS_CPP11;
		}

		static constexpr bool HasCompleteCpp14Support()
		{
			return RADON_COMPILER_SUPPORTS_CPP14;
		}

		static constexpr bool HasCompleteCpp17Support()
		{
			return RADON_COMPILER_SUPPORTS_CPP17;
		}
	};
}

#endif