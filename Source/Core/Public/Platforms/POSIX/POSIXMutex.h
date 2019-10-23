// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_POSIX_MUTEX_H
#define RADON_POSIX_MUTEX_H

#include "PlatformMinimal.h"
#include "PlatformMutex.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

#include <pthread.h>

namespace Radon
{
	struct RADON_API SPlatformMutexAttributesPOSIX : public SPlatformMutexAttributesBase
	{
		typedef SPlatformMutexAttributesPOSIX MyType;
		typedef pthread_mutexattr_t           NativeType;

		SPlatformMutexAttributesPOSIX()
		{
			int32 result = pthread_mutexattr_init(m_pAttributes);
			if (result)
			{
				RADON_LOG()
			}
		}

		~SPlatformMutexAttributesPOSIX()
		{

		}

		FORCEINLINE operator NativeType*() const
		{
			return m_pAttributes;
		}

	private:
		NativeType *m_pAttributes;
	};

	struct RADON_API SPlatformMutexPOSIX : public SPlatformMutexBase
	{
		typedef SPlatformMutexPOSIX           MyType;
		typedef pthread_mutext_t              NativeType;
		typedef SPlatformMutexAttributesPOSIX AttributesType;

		SPlatformMutex()
		{
			pthread_m
		}
		SPlatformMutex(const AttributesType &attributes)
		{

		}

		FORCEINLINE void Destroy()
		{

		}
	};
}

#endif