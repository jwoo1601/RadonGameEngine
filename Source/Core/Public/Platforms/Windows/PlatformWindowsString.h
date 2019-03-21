// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_PLATFORM_WINDOWS_STRING_H
#define RADON_PLATFORM_WINDOWS_STRING_H

#include "PlatformBaseString.h"

#include <Windows.h>

template <typename CharType>
class TStringBuffer { };

namespace Radon
{
	struct SPlatformStringWindows : public SPlatformStringBase
	{
		FORCEINLINE static TStringBuffer<char>& ConvertToUTF8(TStringBuffer<char> buffer, const TChar *source, int32 sourceSize)
		{
			int32 numChars = ::WideCharToMultiByte(CP_UTF8, 0, source, sourceSize, NULL, 0, NULL, NULL);
			if (numChars > 0)
			{
				buffer.Reserve(numChars);

				::WideCharToMultiByte(CP_UTF8, 0, source, sourceSize, buffer.Raw(), numChars, NULL, NULL);
			}

			return buffer;
		}

		FORCEINLINE static TStringBuffer<TChar>& ConvertFromUTF8(TStringBuffer<TChar> buffer, const char *source, int32 sourceSize)
		{
			int32 numChars = ::MultiByteToWideChar(CP_UTF8, 0, source, sourceSize, NULL, 0);
			if (numChars > 0)
			{
				buffer.Reserve(numChars);

				::MultiByteToWideChar(CP_UTF8, 0, source, sourceSize, buffer.Raw(), numChars);
			}

			return buffer;
		}
	};
}

#endif