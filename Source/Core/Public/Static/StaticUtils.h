// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_STATIC_UTILS_H
#define RADON_STATIC_UTILS_H

#include "RadonCore.h"

namespace Radon::Static
{
	// Compile-time helper function that returns the absolute value of {value}
	constexpr int32 GetAbsoluteValue(int32 value)
	{
		return value < 0 ? -value : value;
	}

	// Compile-time helper function that calculates the number of digits in {value} including -(minus) sign in case of negative numbers
	constexpr TSize CalculateNumOfDigits(int32 value)
	{
		return value < 0 ? 1 + CalculateNumOfDigits(-value) : value < 10 ? 1 : 1 + CalculateNumOfDigits(value / 10);
	}

	template <int32... Ints>
	struct TSequence { };

	template <typename T>
	struct TAppend;

	template <int32... Ints>
	struct TAppend<TSequence<Ints...>>
	{
		typedef typename TSequence<Ints..., sizeof...(Ints)> Type;
	};

	template <int32 Int>
	struct TMakeSequenceImpl;

	template <int32 Int>
	using TMakeSequence = typename TMakeSequenceImpl<Int>::Type;

	template <>
	struct TMakeSequenceImpl<0>
	{
		typedef TSequence<> Type;
	};

	template <int32 Int>
	struct TMakeSequenceImpl : TAppend<TMakeSequence<Int - 1>>
	{
		static_assert(Int >= 0, "Int must not be negative");
	};

	template<typename IntType>
	constexpr typename IntType StaticPow(IntType base, IntType exponent)
	{
		return exponent > 0 ? base * StaticPow(base, exponent - 1) : 1;
	}
}

#endif