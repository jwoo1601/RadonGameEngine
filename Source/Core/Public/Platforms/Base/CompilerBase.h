// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_COMPILER_BASE_H
#define RADON_COMPILER_BASE_H

#ifdef __has_cpp_attribute
	#define radon_has_attribute(x)                          __has_cpp_attribute(x)
#else
	#define radon_has_attribute(x)                          0
#endif

#define _RADON_ALIGNOF(x)                                  ((offsetof(Radon::Utils::TAlignofImpl<x>, target)) + 1)

namespace Radon::Utils
{
	template <typename T>
	struct TAlignofImpl
	{
		T target;
	};
}

#endif