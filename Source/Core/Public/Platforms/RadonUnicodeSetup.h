// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_UNICODE_SETUP_H
#define RADON_UNICODE_SETUP_H

#if !RADON_PLATFORM_SUPPORTS_UNICODE && RADON_UNICODE
	#undef  RADON_UNICODE
	#define RADON_UNICODE                               0
	#pragma message("Using unicode on a platform on which it is not supported is not allowed, therefore, RADON_UNICODE was automatically turned off") 
#endif

#endif