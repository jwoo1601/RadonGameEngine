// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_STRING_BUFFER_H
#define RADON_STRING_BUFFER_H

#include "RadonCore.h"
#include "Array.h"

namespace Radon::String
{
	template <typename T, typename = TEnableIf<TIsIntegral<T>>>
	class TStringBuffer
	{
		typedef T CharType;

	public:

		FORCEINLINE CharType* GetRaw();
		FORCEINLINE const CharType* GetRaw() const;

		void Reserve(TSize size);
		
	private:
		TArray<CharType> m_raw;
	};
}

#endif