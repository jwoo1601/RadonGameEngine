// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_STATIC_STRING_H
#define RADON_STATIC_STRING_H

#include "RadonCore.h"
#include "StaticUtils.h"
#include "RadonAssert.h"

namespace Radon::Static
{
	template <TSize Size>
	class TStringLiteral
	{
	public:

		constexpr TStringLiteral(const TChar(&refLiteral)[Size + 1])
			: m_refLiteral
			(
//				RADON_CASSERT(refLiteral[Size] == TEXT('\0')),
				refLiteral
			)
		{ }

		constexpr TChar operator[](TIndex index) const
		{
			return RADON_CASSERT(index >= 0 && index < Size),
				   m_refLiteral[index];
		}

	private:
		const TChar(&m_refLiteral)[Size + 1];
	};

	template <TSize SizeWithNull>
	constexpr auto MakeStringLiteral(const TChar(&refLiteral)[SizeWithNull])
		-> TStringLiteral<SizeWithNull - 1>
	{
		return TStringLiteral<SizeWithNull - 1>(refLiteral);
	}

	// A string class specifically designed for compile-time usage, holding a const array of chars
	template <TSize TotalSize>
	class TStaticString
	{
	public:

		constexpr TStaticString(const TStringLiteral<TotalSize> &refLiteral)
			: TStaticString{ refLiteral,
							 TMakeSequence<TotalSize>{ } }
		{ }

		template <TSize Size1, typename = TEnableIf<Size1 <= TotalSize>>
		constexpr TStaticString(const TStringLiteral<Size1>				&refLiteral1,
								const TStringLiteral<TotalSize - Size1> &refLiteral2)
			: TStaticString{ refLiteral1,
							 refLiteral2,
							 TMakeSequence<Size1>{ },
							 TMakeSequence<TotalSize - Size1>{ } }
		{ }

		constexpr TChar operator[](TIndex index) const
		{
			return RADON_CASSERT(index >= 0 && index < Size()),
				   m_str[index];
		}

		constexpr TSize Size() const
		{
			return sizeof(m_str) / sizeof(TChar) - 1;
		}

		constexpr const TChar* CStr() const
		{
			return m_str;
		}

	private:

		template <TIndex... Indicies>
		constexpr TStaticString(const TStringLiteral<TotalSize> &refLiteral,
								TSequence<Indicies...>)
			: m_str{ refLiteral[Indicies]..., TEXT('\0') }
		{

		}

		template <TSize Size1, TIndex... Indicies1, TIndex... Indicies2>
		constexpr TStaticString(const TStringLiteral<Size1>				&refLiteral1,
								const TStringLiteral<TotalSize - Size1> &refLiteral2,
								TSequence<Indicies1...>,
								TSequence<Indicies2...>)
			: m_str { refLiteral1[Indicies1]..., refLiteral2[Indicies2]..., TEXT('\0') }
		{

		}

	private:
		const TChar m_str[TotalSize + 1];
	};

	template <TSize Size1, TSize Size2>
	constexpr auto operator+(const TStringLiteral<Size1> &refLiteral1, const TStringLiteral<Size2> &refLiteral2)
		-> TStaticString<Size1 + Size2>
	{
		return TStaticString<Size1 + Size2>(refLiteral1, refLiteral2);
	}

	template <TChar... Chars>
	struct TStaticStringBuilder
	{
		typedef typename TStaticString<sizeof...(Chars)> StringType;
		typedef typename TStringLiteral<sizeof...(Chars)> LiteralType;

		static constexpr StringType MakeStaticString()
		{
			return LiteralType({ Chars... });
		}
	};
}

#endif