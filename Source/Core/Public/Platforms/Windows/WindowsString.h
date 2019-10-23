// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_WINDOWS_STRING_H
#define RADON_WINDOWS_STRING_H

#include "PlatformMinimal.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

#include "PlatformString.h"
#include "StringBuffer.h"

#include <Windows.h>

namespace Radon
{
	using namespace String;

	struct SPlatformStringWindows : public SPlatformStringBase
	{
		FORCEINLINE static TStringBuffer<char>& ConvertToUTF8(TStringBuffer<char> &outBuffer, TChar *source)
		{
			TSize sourceLength = Strlen(source);
			int32 numChars = ::WideCharToMultiByte(CP_UTF8, 0, source, sourceLength, NULL, 0, NULL, NULL);

			if (numChars > 0)
			{
				outBuffer.Reserve(numChars);

				::WideCharToMultiByte(CP_UTF8, 0, source, sourceLength, outBuffer.GetRaw(), numChars, NULL, NULL);
			}

			outBuffer += source;

			return outBuffer;
		}

		FORCEINLINE static TStringBuffer<TChar>& ConvertFromUTF8(TStringBuffer<TChar> &buffer, Char8 *source)
		{
			TSize sourceLength = UTF8Strlen(source);
			int32 numChars = ::MultiByteToWideChar(CP_UTF8, 0, source, sourceLength, NULL, 0);

			if (numChars > 0)
			{
				buffer.Reserve(numChars);

				::MultiByteToWideChar(CP_UTF8, 0, source, sourceLength, buffer.GetRaw(), numChars);
			}

			return buffer;
		}
	};
}

#endif