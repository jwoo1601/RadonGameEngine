// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_COMPILER_MSVC_H
#define RADON_COMPILER_MSVC_H

#include "CompilerBase.h"

#define RADON_SUPPORTED_COMPILER			1

#define RADON_COMPILER_MSVC					1
#define RADON_COMPILER_CLANG				0
#define RADON_COMPILER_GCC					0
#define RADON_COMPILER_MINIMAL_VERSION		_MSC_VER
#define RADON_COMPILER_VERSION				_MSC_FULL_VER

#define RADON_COMPILER_SUPPORTS_CPP11		1
#define RADON_COMPILER_SUPPORTS_CPP14
#define RADON_COMPILER_SUPPORTS_CPP17

#define RADON_COMPILER_HAS_NOEXCEPT
#define RADON_COMPILER_HAS_ALIGNOF

namespace Radon::Config
{
	struct SCompilerConfigMSVC : public SCompilerConfigBase
	{
		typedef TCompilerVersion<_MSC_FULL_VER / 10000000,
								 _MSC_FULL_VER / 100000 % 100,
								 _MSC_FULL_VER % 100000,
								 _MSC_BUILD> Version;
	};
}

#endif // !RADON_COMPILER_MSVC_H