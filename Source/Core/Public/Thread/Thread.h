// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_THREAD_H
#define RADON_THREAD_H

#include "RadonCore.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

namespace Radon::Thread
{
	class RADON_API XThread
	{
	public:

		FORCEINLINE void Create() RADON_NOEXCEPT;
		FORCEINLINE void Destroy() RADON_NOEXCEPT;

		void Start() RADON_NOEXCEPT;
		void Stop() RADON_NOEXCEPT;

		void Join() RADON_NOEXCEPT;
		void Sleep(uint32 milliseconds);

		FORCEINLINE SThreadId GetId() RADON_NOEXCEPT;

		static XThread* GetCurrenThread();
		static TSize GetNumHardwareThreads();

	private:
//		SThreadId m_id;
	};
}

#endif