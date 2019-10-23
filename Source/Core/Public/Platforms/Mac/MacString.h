// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_MAC_STRING_H
#define RADON_MAC_STRING_H

#include "PlatformMinimal.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

#include "POSIXString.h"

namespace Radon
{
	struct RADON_API SPlatformStringMac : public SPlatformStringPOSIX
	{

	};
}

#endif