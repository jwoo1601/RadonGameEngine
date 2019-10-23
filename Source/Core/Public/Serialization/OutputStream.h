// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_OUTPUT_STERAM_H
#define RADON_OUTPUT_STREAM_H

#include "RadonCoreMinimal.h"

namespace Radon::Serialization
{
	enum class EOutputStreamFlag : uint8
	{
		None			    = 0x00,
		// sets the byte order of the stream to BE (Big Endian)
		NetworkByteOrder    = 0x01,
		// enables compact serialization
		Allign			    = 0x02,
	};

	class RADON_API XOutputStream
	{
	public:

		XOutputStream();
		virtual ~XOutputStream();

		FORCEINLINE bool HasFlag(uint8 flag)
		{
			return m_flag & flag;
		}

		FORCEINLINE void SetFlag(uint8 flag)
		{
			m_flag |= flag;
		}

		virtual void Close();
		virtual void Flush();

		virtual void Serialize(void *pData, TIndex offset, TSize length);

		virtual XOutputStream& Skip(TSize count);

		FORCEINLINE friend XOutputStream& operator<<(XOutputStream &stream, int8 value)
		{
			Serialize(&value, 0, sizeof(int8));

			return *this;
		}

		FORCEINLINE friend XOutputStream& operator<<(XOutputStream &stream, int16 value)
		{
			Serialize(&value, 0, sizeof(int16));

			return *this;
		}

		FORCEINLINE friend XOutputStream& operator<<(XOutputStream &stream, int32 value)
		{
			Serialize(&value, 0, sizeof(int32));

			return *this;
		}

		FORCEINLINE friend XOutputStream& operator<<(XOutputStream &stream, int64 value)
		{
			Serialize(&value, 0, sizeof(int64));

			return *this;
		}

		FORCEINLINE friend XOutputStream& operator<<(XOutputStream &stream, uint8 value)
		{
			Serialize(&value, 0, sizeof(uint8));

			return *this;
		}

		FORCEINLINE friend XOutputStream& operator<<(XOutputStream &stream, uint16 value)
		{
			Serialize(&value, 0, sizeof(uint16));

			return *this;
		}

		FORCEINLINE friend XOutputStream& operator<<(XOutputStream &stream, uint32 value)
		{
			Serialize(&value, 0, sizeof(uint32));

			return *this;
		}

		FORCEINLINE friend XOutputStream& operator<<(XOutputStream &stream, uint64 value)
		{
			Serialize(&value, 0, sizeof(uint64));

			return *this;
		}

		FORCEINLINE friend XOutputStream& operator<<(XOutputStream &stream, float value)
		{
			Serialize(&value, 0, sizeof(float));

			return *this;
		}

		FORCEINLINE friend XOutputStream& operator<<(XOutputStream &stream, double value)
		{
			Serialize(&value, 0, sizeof(double));

			return *this;
		}

		FORCEINLINE friend XOutputStream& operator<<(XOutputStream &stream, long double value)
		{
			Serialize(&value, 0, sizeof(long double));

			return *this;
		}

		FORCEINLINE friend XOutputStream& operator<<(XOutputStream &stream, char value)
		{
			Serialize(&value, 0, sizeof(char));

			return *this;
		}

		FORCEINLINE friend XOutputStream& operator<<(XOutputStream &stream, TChar value)
		{
			Serialize(&value, 0, sizeof(TChar));

			return *this;
		}

	private:
		uint8 m_flag;
	};
}

#endif