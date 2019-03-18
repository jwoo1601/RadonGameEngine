// Copyright 2019 Simon Kim All Rights Reserved.

#pragma once

#include "RadonCore.h"

namespace Radon
{
	template <typename T, TSize Size>
	class RADONCORE_API TStaticArray
	{
		typedef TImmutableArray<T> MyType;

	public:
		typedef T ElementType;

	public:

		// Constructors
		TStaticArray();

		// Destructors
		~TStaticArray();
	};
}