// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_STATIC_CONVERTER_H
#define RADON_STATIC_CONVERTER_H

#include "RadonCore.h"
#include "StaticUtils.h"
#include "StaticString.h"
#include "RadonTemplates.h"

namespace Radon::Static
{
	// A numeric string builder designed for compile-time usage (in case of numbers of 3 or more digits)
	template <typename IntType, TSize Size, IntType Value, TChar... Chars>
	struct TStaticItoaImpl
	{
		static_assert(TIsIntegral<IntType> == true, "IntType must be an integeral type");

		typedef typename TStaticItoaImpl<IntType, Size - 1, Value / 10, TEXT('0') + GetAbsoluteValue(Value) % 10, Chars...>::Type Type;
	};

	// Specialization of {TStaticItoaImpl} for two-digit-numbers
	template <typename IntType, IntType Value, TChar... Chars>
	struct TStaticItoaImpl<IntType, 2, Value, Chars...>
	{
		typedef TStaticStringBuilder < Value < 0 ? TEXT('-') : TEXT('0') + Value / 10, TEXT('0') + GetAbsoluteValue(Value) % 10, Chars...> Type;
	};

	// Specialization of {TStaticItoaImpl} for positive one-digit-numbers
	template <typename IntType, IntType Value, TChar... Chars>
	struct TStaticItoaImpl<IntType, 1, Value, Chars...>
	{
		typedef TStaticStringBuilder<TEXT('0') + Value, Chars...> Type;
	};

	template <int32 Value, TSize NumDigits = CalculateNumOfDigits(Value)>
	constexpr auto Itoa32()
		-> typename TStaticItoaImpl<int32, NumDigits, Value>::Type::StringType
	{
		return TStaticItoaImpl<int32, NumDigits, Value>::Type::MakeStaticString();
	}

	template <int64 Value, TSize NumDigits = CalculateNumOfDigits(Value)>
	constexpr auto Itoa64()
		-> typename TStaticItoaImpl<int64, NumDigits, Value>::Type::StringType
	{
		return TStaticItoaImpl<int64, NumDigits, Value>::Type::MakeStaticString();
	}

	/*
	template <typename IntType, IntType Value, TIndex Num, TChar... Chars>
	struct TStaticAtoiImpl
	{
		static_assert(TIsIntegral<IntType>, "IntType must be an integeral type");

		static constexpr IntType Result = TStaticAtoiImpl < IntType, Value + TEXT('0') - TStringLiteral({ Chars... })[Num - 1] / StaticPow<IntType>(10, (sizeof...(Chars) - Num)), Num - 1, Chars... > ::Result;
	};

	template <typename IntType, IntType Value, TChar... Chars>
	struct TStaticAtoiImpl<IntType, Value, 0, Chars...>
	{
		static constexpr IntType Result = Value;
	};

	template <TSize Size>
	constexpr int32 StaticAtoi32(const TStringLiteral<Size> &str)
	{
		return StaticAtoiInternal<int32>(str, TMakeSequence<Size>{});
	}

	template <typename IntType, TSize Size, TIndex... Indicies>
	constexpr IntType StaticAtoiInternal(const TStringLiteral<Size> &str, TSequence<Indicies...>)
	{
		return TStaticAtoiImpl<IntType, 0, Size, str[Indicies]...>::Result;
	}

	int sdfasd()
	{
		constexpr auto sdds = StaticAtoi32(MakeStringLiteral(TEXT("123")));

		return 0;
	}
	*/
}

#endif