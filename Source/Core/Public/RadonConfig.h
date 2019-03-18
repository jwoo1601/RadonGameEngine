// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_CONFIG_H
#define RADON_CONFIG_H

#define RADON_VERSION			 100
#define RADON_VERSION_STRING	"1.0.0"

#ifndef RADON_DEBUG
	#if defined(_DEBUG)
		#define RADON_DEBUG						1
	#else
		#define RADON_DEBUG						0
	#endif
#endif

#ifndef RADON_RELEASE
	#if defined(NDEBUG)
		#define RADON_RELEASE					1
	#else
		#define RADON_RELEASE					0
	#endif
#endif


#ifndef RADON_ENABLE_MEMORY_PROFILE
	#define RADON_ENABLE_MEMORY_PROFILE			1
#endif

#ifndef RADON_ENABLE_ASSERTION
	#define RADON_ENABLE_ASSERTION				1
	#include "RadonAssert.h"
#endif

#endif