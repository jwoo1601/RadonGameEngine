// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_COMPILER_BASE_H
#define RADON_COMPILER_BASE_H

#include "PlatformTypes.h"

namespace Radon::Config
{
	template <uint32 M, uint32 R, uint32 P, uint32 B>
	struct TCompilerVersion
	{
		constexpr uint32 Major()
		{
			return M;
		}

		constexpr uint32 Revision()
		{
			return R;
		}

		constexpr uint32 Patch()
		{
			return P;
		}

		constexpr uint32 Build()
		{
			return B;
		}
	};

	struct SCompilerConfigBase
	{
		typedef TCompilerVersion<0, 0, 0, 0> Version;
//		typedef typename __ VersionString;

		constexpr const TChar* GetVersionString()
		{
			return nullptr;
		}
	};
}

#endif