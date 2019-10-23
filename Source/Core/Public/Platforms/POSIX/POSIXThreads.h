// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_POSIX_THREADS_H
#define RADON_POSIX_THREADS_H

#include "PlatformMinimal.h"
#include "PlatformThreads.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

#include <pthread.h>

namespace Radon
{
	struct RADON_API SThreadIdPOSIX : public SThreadIdBase
	{
		typedef SThreadIdPOSIX MyType;
		typedef pthread_t      NativeType;

		SThreadIdPOSIX();
		SThreadIdPOSIX(NativeType handle);

		FORCEINLINE void SetNativeHandle(NativeType handle)
		{
			m_handle = handle;
		}

		FORCEINLINE NativeType GetNativeHandle()
		{
			return m_handle;
		}

		FORCEINLINE operator NativeType*() const
		{
			return &m_handle;
		}

		FORCEINLINE bool operator==(const MyType &rhs) const
		{
			return pthread_equal(m_handle, rhs.m_handle) == 0;
		}

		FORCEINLINE bool operator!=(const MyType &rhs) const
		{
			return !(*this == rhs);
		}

		
	private:
		NativeType m_handle;
	};

	struct RADON_API SThreadAttributesPOSIX : public SThreadAttributesBase
	{
		CLASS_NOT_COPYABLE(SThreadAttributesPOSIX);

		typedef SThreadAttributesPOSIX MyType;
		typedef pthread_attr_t         NativeType;

		SThreadAttributesPOSIX()
		{
			int32 result = pthread_attr_init(m_pAttributes);
			if (result)
			{
				RADON_LOG(PlatformLog, "Failed to create a native thread attributes object; native error code: %d", result);
				m_pAttribute = nullptr;
			}
		}

		~SThreadAttributesPOSIX()
		{
			if (m_pAttributes)
			{
				pthread_attr_destroy(pAttribute);
			}
		}

		FORCEINLINE bool IsDetached() const
		{
			return GetDetachState() == PTHREAD_CREATE_DETACHED;
		}

		FORCEINLINE void SetDetached()
		{
			pthread_attr_setdetachstate(m_pAttributes, PTHREAD_CREATE_DETACHED);
		}

		FORCEINLINE bool IsJoinable() const
		{
			return GetDetachState() == PTHREAD_CREATE_JOINABLE;
		}

		FORCEINLINE void SetJoinable()
		{
			pthread_attr_setdetachstate(m_pAttributes, PTHREAD_CREATE_JOINABLE);
		}

		FORCEINLINE TSize GetStackSize() const
		{
			TSize stackSize;
			pthread_attr_getstacksize(m_pAttributes, &stackSize);

			return stackSize;
		}

		FORCEINLINE void SetStackSize(TSize stackSize)
		{
			pthread_attr_setstacksize(m_pAttributes, stackSize);
		}

		FORCEINLINE void* GetStackAddress() const
		{
			void *pStackAddress;
			pthread_attr_getstackaddr(m_pAttributes, &pStackAddress);

			return pStackAddress;
		}

		FORCEINLINE void SetStackAddress(void *pStackAddress)
		{
			pthread_attr_setstackaddr(m_pAttributes, pStackAddress);
		}

		FORCEINLINE operator NativeType*() const
		{
			return m_pAttributes;
		}

	private:

		FORCEINLINE int32 GetDetachState() const
		{
			int32 detachState;
			pthread_attr_getdetachstate(m_pAttributes, &detachState);

			return detachState;
		}

	private:
		pthread_attr_t *m_pAttributes;
	};

	struct RADON_API SPlatformThreadsPOSIX : public SPLatformThreadsBase
	{
		typedef SThreadIdPOSIX         IdType;
		typedef SThreadAttributesPOSIX AttributesType;

		template <typename Routine>
		static FORCEINLINE bool CreateThread(IdType &outThreadId, const AttributesType &attributes, Routine startRoutine, void *pParam)
		{
			int32 result = pthread_create(outThreadId, attributes, startRoutine, pParam);
			if (result)
			{
				RADON_LOG(PlatformLog, "Failed to create a native thread; native error code: %d", result);
			}

			return result == 0;
		}

		static FORCEINLINE bool TerminateThread(IdType threadid)
		{

		}

		static FORCEINLINE void ExitCurrentThread(int32 exitCode)
		{
			pthread_exit(exitCode);
		}

		static FORCEINLINE void* JoinThread(IdType threadId)
		{
			// Note: pResult must not be a local variable of the terminated thread
			void *pTerminationResult;

			int32 result = pthread_join(threadId, &pTerminationResult);
			if (result)
			{
				RADON_LOG(PlatformLog, "Failed to join a native thread; native error code: %d", result);
			}

			return pResult;
		}

		static FORCEINLINE void DetachThread(IdType threadId)
		{
			pthread_detach()
		}

		static FORCEINLINE IdType GetCurrentThreadId()
		{
			return IdType(pthread_self(void));
		}

		static FORCEINLINE void Startup()
		{

		}

		static FORCEINLINE void Cleanup()
		{
			pthread_exit(NULL);
		}
	};
}

#endif