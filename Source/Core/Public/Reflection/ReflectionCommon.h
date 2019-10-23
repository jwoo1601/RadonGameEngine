// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_ACCESS_LEVEL_H
#define RADON_ACCESS_LEVEL_H

#include "RadonCoreMinimal.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
#pragma once
#endif

namespace Radon::Reflection
{
#define NOT_EXPOSED()

	enum class EAccessLevel : uint8
	{
		Public,
		Protected,
		Private
	};

	enum class EQualifier : uint8
	{
		None     = 0x00,

		/* Generic qualifiers */
		Const    = 0x01,
		Volatile = 0x02,
		Static   = 0x04,

		/* Function-specific qualifiers */
		Noexcept = 0x08,

		/* Class-specific qualifiers */
		Final    = 0x0F
	};
}

#endif