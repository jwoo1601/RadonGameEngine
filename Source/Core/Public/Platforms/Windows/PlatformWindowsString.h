// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_PLATFORM_WINDOWS_STRING_H
#define RADON_PLATFORM_WINDOWS_STRING_H

#include "PlatformBaseString.h"

#include <Windows.h>

namespace Radon
{
	struct SPlatformStringWindows : public SPlatformStringBase
	{

		static char* ConvertToUTF8(char *to, const TChar *from)
		{

		}

		static TChar* ConvertFromUTF8(TChar *to, const char *from)
		{

		}
	};
}

#endif