// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_CLANG_CONFIG_H
#define RADON_CLANG_CONFIG_H

#include "PlatformMinimal.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

#include "CompilerBaseConfig.h"

namespace Radon::Config
{
	struct RADON_API SCompilerConfigClang : public SCompilerConfigBase
	{
		typedef TCompilerVersion<__clang_major__,
			                     __clang_minor__,
			                     __clang_patchlevel__,
			                     0> Version;
	};
}

#endif