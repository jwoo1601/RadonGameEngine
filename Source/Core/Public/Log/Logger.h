// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_LOGGER_H
#define RADON_LOGGER_H

#include "RadonCoreMinimal.h"

namespace Radon::Log
{
	const TSize LoggerBufferSize = 1024;

	enum class EVerbosity : uint8
	{
		Trace    = 0x01,
		Info     = 0x02,
		Warning  = 0x03,
		Error    = 0x04,
		Fatal    = 0x05,
		Verbose  = 0x06
	};

	class RADON_API XLogger
	{
	public:

		template <typename... Args>
		int32 Log(const TChar *formatString, const Args &...args)
		{

		}

		template <typename... Args>
		int32 VerboseLog(EVerbosity verbosity, const TChar *formatString, const Args &...args)
		{

		}

		template <typename... Args>
		int32 LogImpl(const TChar *formatString, const Args &...args)
		{
			int32 numCharsWritten = vsnprintf(buffer, LoggerBufferSize, format, args);

			OutputDebugString(buffer);

			return numCharsWritten;
		}

	private:
		TChar buffer[LoggerBufferSize];
	};
}

#endif