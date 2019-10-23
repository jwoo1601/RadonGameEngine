// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_LOG_H
#define RADON_LOG_H

#include "RadonPlatform.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

#if RADON_DEBUG
	#define RADON_LOG(category, msg, ...)
#else
	#define RADON_LOG(...) ((void)0)
#endif

#define CREATE_LOG_CHANNEL(name, verbosity)

#endif