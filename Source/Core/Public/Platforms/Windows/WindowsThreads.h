// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_WINDOWS_THREADS_H
#define RADON_WINDOWS_THREADS_H

#include "PlatformMinimal.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

#include "PlatformThreads.h"

#include <Windows.h>

namespace Radon
{
	struct RADON_API SThreadIdWindows : public SThreadIdBase
	{
		typedef HANDLE NativeType;

		SThreadIdWindows(NativeType handle)
			: m_handle(handle)
		{

		}

		FORCEINLINE NativeType GetNativeHandle()
		{
			return m_handle;
		}

	private:
		NativeType m_handle;
	};

	struct RADON_API SThreadAttributesWindows : public SThreadAttributesBase
	{
		SThreadAttributesWindows()
		{

		}

		~SThreadAttributesWindows()
		{

		}

	private:
		LPSECURITY_ATTRIBUTES pSecurityAttributes;
		TSize                 stackSize;
		DWORD                 flags
	};

	struct RADON_API SPlatformThreadsWindows : public SPlatformThreadsBase
	{
		typedef SThreadIdWindows         IdType;
		typedef SThreadAttributesWindows AttributesType;

	/*	LPSECURITY_ATTRIBUTES  pSecurityAttributes;
		TSize                  stackSize;
		LPTHREAD_START_ROUTINE pStartAddress;
		LPVOID                 pParameters;
		DWORD                  flags;
		LPDWORD                pThreadId; */

		template <typename Routine>
		static FORCEINLINE IdType CreateThread(const AttributesType &attributes, Routine startRoutine, void *pParam)
		{
			return ::CreateThread(params.pAttributes,
				                  params.stackSize,
				                  params.pStartAddress,
				                  params.pParameters,
				                  params.flags,
				                  params.pThreadId
				                 );
		}

		static FORCEINLINE int32 SuspendThread(IdType tid)
		{
			return ::SuspendThread(tid.GetNativeHandle());
		}

		static FORCEINLINE bool TerminateThread(IdType tid, int32 exitCode)
		{
			return ::TerminateThread(tid.GetNativeHandle(), exitCode);
		}

		static FORCEINLINE IdType GetCurrentThread()
		{
			return ::GetCurrentThread();
		}
	};
}

#endif