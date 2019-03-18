// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_STATIC_CONVERTER_H
#define RADON_STATIC_CONVERTER_H

#include "RadonCore.h"
#include "StaticUtils.h"
#include "StaticString.h"

namespace Radon::Static
{
	// A numeric string builder designed for compile-time usage (in case of numbers of 3 or more digits)
	template <TSize Size, int32 Value, TChar... Args>
	struct TStaticNumericConverter
	{
		typedef typename TStaticNumericConverter<Size - 1, Value / 10, TEXT('0') + GetAbsoluteValue(Value) % 10, Args...>::Type Type;
	};

	// Specialization of {TStaticNumericConverter} for two-digit-numbers
	template <int32 Value, TChar... Args>
	struct TStaticNumericConverter<2, Value, Args...>
	{
		typedef TStaticString<Value < 0 ? TEXT('-') : TEXT('0') + Value / 10, TEXT('0') + GetAbsoluteValue(Value) % 10, Args...> Type;
	};

	// Specialization of {TStaticNumericConverter} for positive one-digit-numbers
	template <int32 Value, TChar... Args>
	struct TStaticNumericConverter<1, Value, Args...>
	{
		typedef TStaticStringBuilder<TEXT('0') + Value, Args...>::StringType Type;
	};

	template <int32 Value>
	class TStaticNumericString
	{
	public:
		static constexpr TSize NumDigits = CalculateNumOfDigits(Value);

	private:
		typedef typename TStaticNumericConverter<NumDigits, Value>::Type Type;

	public:

		static constexpr const TChar* CStr()
		{
			return Value.data;
		}

	private:
		static constexpr Type Value{};
	};

	template<int32 Value>
	constexpr typename TStaticNumericString<Value>::Type TStaticNumericString<Value>::Value;
}

#endif