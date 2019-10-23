// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_COMPILER_UTILS_H
#define RADON_COMPILER_UTILS_H

#include "PlatformMinimal.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

namespace Radon::Utils
{
	template <uint32 M, uint32 R, uint32 P, uint32 B>
	struct TCompilerVersion
	{
		static constexpr uint32 Major = M;
		static constexpr uint32 Revision = R;
		static constexpr uint32 Patch = P;
		static constexpr uint32 Build = B;
	};
}

#endif