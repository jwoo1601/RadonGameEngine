// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_PLATFORM_STRING_H
#define RADON_PLATFORM_STRING_H

#include "PlatformMinimal.h"

#if RADON_PLATFORM_SUPPORTS_UNICODE
	#define TEXT(x)		L##x
#else
	#define TEXT(x)     x
#endif

#include "RadonConfig.h"
#include "RadonDefines.h"
#include "StringBuffer.h"

#if RADON_UNICODE
	#include <wchar.h>
#else
	#include <string.h>
#endif

#include <stdarg.h>

namespace Radon
{
	using namespace String;

	struct RADON_API SPlatformStringBase
	{
		FORCEINLINE static TChar* Strcat(TChar *destination, const TChar *source)
		{
			#if RADON_UNICODE
				return ::wcscat(destination, source);
			#else
				return ::strcat(destination, source);
			#endif
		}

		FORCEINLINE static TChar* Strncat(TChar *destination, const TChar *source, TSize num)
		{
			#if RADON_UNICODE
				return ::wcsncat(destination, source, num);
			#else
				return ::strncat(destination, source, num);
			#endif
		}

		FORCEINLINE static int32 Strcmp(const TChar *str1, const TChar *str2)
		{
			#if RADON_UNICODE
				return ::wcscmp(str1, str2);
			#else
				return ::strcmp(str1, str2);
			#endif
		}

		FORCEINLINE static int32 Strncmp(const TChar *str1, const TChar *str2, TSize num)
		{
			#if RADON_UNICODE
				return ::wcsncmp(str1, str2, num);
			#else
				return ::strncmp(str1, str2, num);
			#endif
		}

		FORCEINLINE static TChar* Strcpy(TChar *destination, const TChar *source)
		{
			#if RADON_UNICODE
				return ::wcscpy(destination, source);
			#else
				return ::strcpy(destination, source);
			#endif
		}

		FORCEINLINE static TChar* Strncpy(TChar *destination, const TChar *source, TSize num)
		{
			#if RADON_UNICODE
				return ::wcsncpy(destination, source, num);
			#else
				return ::strncpy(destination, source, num);
			#endif
		}

		FORCEINLINE static TSize Strlen(const TChar *str)
		{
			#if RADON_UNICODE
				return ::wcslen(str);
			#else
				return ::strlen(str);
			#endif
		}

		FORCEINLINE static TChar* Strstr(TChar *str, const TChar *substr)
		{
			#if RADON_UNICODE
				return ::wcsstr(str, substr);
			#else
				return ::strstr(str, substr);
			#endif
		}

		FORCEINLINE static const TChar* Strstr(const TChar *str, const TChar *substr)
		{
			#if RADON_UNICODE
				return ::wcsstr(str, substr);
			#else
				return ::strstr(str, substr);
			#endif
		}

		FORCEINLINE static TChar* Strchr(TChar *str, TChar ch)
		{
			#if RADON_UNICODE
				return ::wcschr(str, ch);
			#else
				return ::strchr(str, ch);
			#endif
		}

		FORCEINLINE static const TChar* Strchr(const TChar *str, TChar ch)
		{
			#if RADON_UNICODE
				return ::wcschr(str, ch);
			#else
				return ::strchr(str, ch);
			#endif
		}

		FORCEINLINE static TChar* Strrchr(TChar *str, TChar ch)
		{
			#if RADON_UNICODE
				return ::wcsrchr(str, ch);
			#else
				return ::strrchr(str, ch);
			#endif
		}

		FORCEINLINE static const TChar* Strrchr(const TChar *str, TChar ch)
		{
			#if RADON_UNICODE
				return ::wcsrchr(str, ch);
			#else
				return ::strrchr(str, ch);
			#endif
		}

		FORCEINLINE static TChar* Strtok(TChar *str, const TChar *delimiters)
		{
			#if RADON_UNICODE
				return ::wcstok(str, delimiters);
			#else
				return ::strtok(str, delimiters);
			#endif
		}

		FORCEINLINE static int32 SPrintf(TChar *buffer, const TChar *format, ...)
		{
			int32 result;
			va_list args;
			va_start(args, format);

#			if RADON_UNICODE
				result = vswprintf(buffer, format, args);
			#else
				result = vsprintf(buffer, foramt, args);
			#endif

			va_end(args);

			return result;
		}

		FORCEINLINE static int32 SafeSPrintf(TChar *buffer, TSize bufferSize, const TChar *format, ...)
		{
			int32 result;
			va_list args;
			va_start(args, format);

#			if RADON_UNICODE
			result = vswprintf(buffer, format, args);
#else
			result = vsprintf(buffer, foramt, args);
#endif

			va_end(args);

			return result;
		}

		FORCEINLINE static TSize UTF8Strlen(const Char8 *str)
		{
			TSize length = 0;

			while (*str)
			{
				length += (*str & 0xC0) != 0x80;
			}

			return length;
		}

		/* converts an engine-specific string (TChar) to UTF-8 format */
		FORCEINLINE static TStringBuffer<Char8>& ConvertToUTF8(TStringBuffer<Char8> &outBuffer, TChar *source) ABSTRACT_BODY(return buffer);

		/* converts UTF-8 format to the engine-specific char format (TChar) */
		FORCEINLINE static TStringBuffer<TChar>& ConvertFromUTF8(TStringBuffer<TChar> &outBuffer, Char8 *source) ABSTRACT_BODY(return buffer);
	};
}

#endif