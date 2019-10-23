// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_CONFIG_H
#define RADON_CONFIG_H

#define RADON_VERSION                                "0.2.0 Alpha"
                                                                   // MM|RR|PP
#define RADON_MINIMAL_VERSION                        200           // 00|02|00

#define RADON_VERSION_MAJOR                          0
#define RADON_VERSION_MINOR                          2
#define RADON_VERSION_PATCH                          0
#define RADON_VERSION_TYPE                           "Alpha"


#ifdef _DEBUG
	#define RADON_DEBUG                              1
#else
	#define RADON_DEBUG                              0
#endif

#ifdef NDEBUG
	#define RADON_RELEASE                            1
#else
	#define RADON_RELEASE                            0
#endif

#if RADON_DEBUG
	#define RADON_ENABLE_MEMORY_PROFILE              1
	#define RADON_ENABLE_ASSERTION                   1
#else
	#define RADON_ENABLE_MEMORY_PROFILE              0
	#define RADON_ENABLE_ASSERTION                   0
#endif


#define RADON_UNICODE                                1
#define RADON_SIMD                                   1

#endif