// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_STRING_BUFFER_H
#define RADON_STRING_BUFFER_H

#include "RadonCoreMinimal.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

#include "Array.h"
#include "String.h"

namespace Radon::String
{
	template <typename T, typename = TEnableIf<TIsIntegral<T>>>
	class TStringBuffer
	{
		typedef T CharType;

	public:

		TStringBuffer();
		TStringBuffer(const CharType *rawString);
		TStringBuffer(const XString &string);

		FORCEINLINE CharType* GetRaw();
		FORCEINLINE const CharType* GetRaw() const;

		void Reserve(TSize size);
		TSize Capacity() const;

		XString ToString();
		
	private:
		TArray<CharType> m_raw;
	};
}

#endif