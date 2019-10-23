// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_COMPILER_H
#define RADON_COMPILER_H

#if defined(_MSC_VER)
	#include "CompilerMSVC.h"
#elif defined(__clang__)
	#include "CompilerClang.h"
#elif defined(__GNUC__)
	#include "CompilerGCC.h"
#else
	#include "CompilerDefault.h"
#endif

/* namespace Radon::Config
{
#if RADON_COMPILER_MSVC
	typedef SCompilerConfigMSVC			SCompilerConfig;

#elif RADON_COMPILER_CLANG
	typedef SCompilerConfigClang		SCompilerConfig;

#elif RADON_COMPILER_GCC
	typedef SCompilerConfigGCC			SCompilerConfig;

#else
	typedef SCompilerConfigDefault		SCompilerConfig;

#endif
} */

#endif