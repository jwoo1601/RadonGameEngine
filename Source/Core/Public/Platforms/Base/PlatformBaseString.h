// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_PLATFORM_BASE_STRING_H
#define RADON_PLATFORM_BASE_STRING_H

#define TEXT(x)		L##x

#include <wchar.h>

#include "PlatformTypes.h"

namespace Radon
{
	struct SPlatformStringBase
	{
		static TChar* Strcat(TChar *destination, const TChar *source)
		{
			return ::wcscat(destination, source);
		}

		static TChar* Strncat(TChar *destination, const TChar *source, TSize num)
		{
			return ::wcsncat(destination, source, num);
		}

		static int32 Strcmp(const TChar *str1, const TChar *str2)
		{
			return ::wcscmp(str1, str2);
		}

		static int32 Strncmp(const TChar *str1, const TChar *str2, TSize num)
		{
			return ::wcsncmp(str1, str2, num);
		}

		static TChar* Strcpy(TChar *destination, const TChar *source)
		{
			return ::wcscpy(destination, source);
		}

		static TChar* Strncpy(TChar *destination, const TChar *source, TSize num)
		{
			return ::wcsncpy(destination, source, num);
		}

		static TSize Strlen(const TChar *str)
		{
			return ::wcslen(str);
		}

		static TChar* Strstr(TChar *str, const TChar *substr)
		{
			return ::wcsstr(str, substr);
		}

		static const TChar* Strstr(const TChar *str, const TChar *substr)
		{
			return ::wcsstr(str, substr);
		}

		static TChar* Strchr(TChar *str, TChar ch)
		{
			return ::wcschr(str, ch);
		}

		static const TChar* Strchr(const TChar *str, TChar ch)
		{
			return ::wcschr(str, ch);
		}

		static TChar* Strrchr(TChar *str, TChar ch)
		{
			return ::wcsrchr(str, ch);
		}

		static const TChar* Strrchr(const TChar *str, TChar ch)
		{
			return ::wcsrchr(str, ch);
		}

		// Thread-unsafe
		static TChar* Strtok(TChar *str, const TChar *delimiters)
		{
			return ::wcstok(str, delimiters);
		}

		static char* ConvertToUTF8(char *to, const TChar *from)
		{

		}

		static TChar* ConvertFromUTF8(TChar *to, const char *from)
		{

		}
	};
}

#endif