// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_LOG_H
#define RADON_LOG_H

#include "RadonCore.h"

namespace Radon::Log
{
	const tsize LoggerBufferSize = 1024;

	enum class EVerbosity
	{
		Trace,
		Info,
		Warning,
		Error,
		Fatal,
		Verbose
	};

	class RADON_API VLogger
	{
	public:

		template <typename... Args>
		int32 Log(const tchar *formatString, const Args &...args)
		{

		}

		template <typename... Args>
		int32 VerboseLog(EVerbosity verbosity, const tchar *formatString, const Args &...args)
		{

		}

		template <typename... Args>
		int32 LogImpl(const tchar *formatString, const Args &...args)
		{
			int32 numCharsWritten = vsnprintf(buffer, LoggerBufferSize, format, args);

			OutputDebugString(buffer);

			return numCharsWritten;
		}

	private:
		tchar buffer[LoggerBufferSize];
	};
}

#endif