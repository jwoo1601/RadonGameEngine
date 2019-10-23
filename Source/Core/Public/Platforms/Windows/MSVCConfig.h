// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_MSVC_CONFIG_H
#define RADON_MSVC_CONFIG_H

#include "PlatformMinimal.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

#include "CompilerBaseConfig.h"

namespace Radon::Config
{
	struct RADON_API SCompilerConfigMSVC : public SCompilerConfigBase
	{
		typedef TCompilerVersion<_MSC_FULL_VER / 10000000,
			                     _MSC_FULL_VER / 100000 % 100,
			                     _MSC_FULL_VER % 100000,
			                     _MSC_BUILD> Version;
	};
}

#endif