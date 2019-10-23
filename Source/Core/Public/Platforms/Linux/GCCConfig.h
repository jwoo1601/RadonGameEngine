// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_GCC_CONFIG_H
#define RADON_GCC_CONFIG_H

#include "PlatformMinimal.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

#include "CompilerBaseConfig.h"

namespace Radon::Config
{
	struct RADON_API SCompilerConfigGCC : public SCompilerConfigBase
	{
		typedef TCompilerVersion<__GNUC__,
			                     __GNUC_MINOR__,
			                     __GNUC_PATCHLEVEL__,
			                     0> Version;
	};
}

#endif