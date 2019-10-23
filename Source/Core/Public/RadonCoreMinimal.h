// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_CORE_MINIMAL_H
#define RADON_CORE_MINIMAL_H

#include "RadonPlatform.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

// The header files below must not include this file (RadonCoreMinimal.h)
#include "RadonConfig.h"
#include "RadonDefines.h"
#include "RadonTemplates.h"
#include "RadonAssert.h"
#include "RadonLog.h"

#endif