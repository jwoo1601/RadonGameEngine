// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_POSIX_STRING_H
#define RADON_POSIX_STRING_H

#include "PlatformMinimal.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

#include "PlatformString.h"
#include "StringBuffer.h"

#include <iconv.h>

namespace Radon
{
	using namespace String;

	struct RADON_API SPlatformStringPOSIX : public SPlatformStringBase
	{
		FORCEINLINE static TStringBuffer<Char8>& ConvertToUTF8(TStringBuffer<Char8> &outBuffer, TChar *source)
		{
			#if RADON_UNICODE
				iconv_t conversionDescriptor = iconv_open("UTF-8", "wchar_t");
			#else
				iconv_t conversionDescriptor = iconv_open("UTF-8", "char");
			#endif

			if (conversionDescriptor == (iconv_t)-1)
			{
				// error
			}

			TSize sourceLength = Strlen(source);
			TSize maxConvertedStringLength = 4 * sourceLength;

			outBuffer.Reserve(maxConvertedStringLength);
			Char8 *rawBuffer = outBuffer.GetRaw();

			iconv(conversionDescriptor, &source, &sourceLength, &rawBuffer, &maxConvertedStringLength);
			iconv_close(conversionDescriptor);

			return outBuffer;
		}

		FORCEINLINE static TStringBuffer<TChar>& ConvertFromUTF8(TStringBuffer<TChar> &outBuffer, Char8 *source)
		{
			#if RADON_UNICODE
				iconv_t conversionDescriptor = iconv_open("wchar_t", "UTF-8");
			#else
				iconv_t conversionDescriptor = iconv_open("char", "UTF-8");
			#endif

			if (conversionDescriptor == (iconv_t)-1)
			{
				// error
			}

			TSize sourceLength = UTF8Strlen(source);
			TSize convertedLength = sizeof(TChar) * sourceLength;

			outBuffer.Reserve(convertedLength);
			TChar *rawBuffer = outBuffer.GetRaw();

			iconv(conversionDescriptor, &source, &sourceLength, &rawBuffer, &convertedLength);
			iconv_close(conversionDescriptor);

			return outBuffer;
		}
	};
}

#endif