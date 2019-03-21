// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_COMPILER_BASE_H
#define RADON_COMPILER_BASE_H

#include "PlatformTypes.h"

namespace Radon::Config
{
	template <typename T>
	struct TAlignofImpl
	{
		T target;
	};

#define _RADON_ALIGNOF(x) ((offsetof(TAlignofImpl<x>, target)) + 1)

	template <uint32 M, uint32 R, uint32 P, uint32 B>
	struct TCompilerVersion
	{
		static constexpr uint32 Major = M;
		static constexpr uint32 Revision = R;
		static constexpr uint32 Patch = P;
		static constexpr uint32 Build = B;
	};

	struct SCompilerConfigBase
	{
		typedef TCompilerVersion<0, 0, 0, 0> Version;
	};
}

#endif