// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_INPUT_STERAM_H
#define RADON_INPUT_STREAM_H

#include "RadonCore.h"

namespace Radon::Serialization
{
	enum class EInputStreamFlag : uint8
	{
		None = 0x00,
		// sets the byte order of the stream to BE (Big Endian)
		NetworkByteOrder = 0x01,
		// enables compact serialization
		Allign = 0x02,
	};

	class RADON_API XInputStream
	{
	public:

		XInputStream();
		virtual ~XInputStream();

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

		virtual void Deserialize(void *pData, TIndex offset, TSize length);

		virtual XInputStream& Skip(TSize count);

		FORCEINLINE friend XInputStream& operator>>(XInputStream &stream, int8 &value)
		{
			Deserialize(&value, 0, sizeof(int8));

			return *this;
		}

		FORCEINLINE friend XInputStream& operator>>(XInputStream &stream, int16 &value)
		{
			Deserialize(&value, 0, sizeof(int16));

			return *this;
		}

		FORCEINLINE friend XInputStream& operator>>(XInputStream &stream, int32 &value)
		{
			Deserialize(&value, 0, sizeof(int32));

			return *this;
		}

		FORCEINLINE friend XInputStream& operator>>(XInputStream &stream, int64 &value)
		{
			Deserialize(&value, 0, sizeof(int64));

			return *this;
		}

		FORCEINLINE friend XInputStream& operator>>(XInputStream &stream, uint8 &value)
		{
			Deserialize(&value, 0, sizeof(uint8));

			return *this;
		}

		FORCEINLINE friend XInputStream& operator>>(XInputStream &stream, uint16 &value)
		{
			Deserialize(&value, 0, sizeof(uint16));

			return *this;
		}

		FORCEINLINE friend XInputStream& operator>>(XInputStream &stream, uint32 &value)
		{
			Deserialize(&value, 0, sizeof(uint32));

			return *this;
		}

		FORCEINLINE friend XInputStream& operator>>(XInputStream &stream, uint64 &value)
		{
			Deserialize(&value, 0, sizeof(uint64));

			return *this;
		}

		FORCEINLINE friend XInputStream& operator>>(XInputStream &stream, float &value)
		{
			Deserialize(&value, 0, sizeof(float));

			return *this;
		}

		FORCEINLINE friend XInputStream& operator>>(XInputStream &stream, double &value)
		{
			Deserialize(&value, 0, sizeof(double));

			return *this;
		}

		FORCEINLINE friend XInputStream& operator>>(XInputStream &stream, long double &value)
		{
			Deserialize(&value, 0, sizeof(long double));

			return *this;
		}

		FORCEINLINE friend XInputStream& operator>>(XInputStream &stream, char &value)
		{
			Deserialize(&value, 0, sizeof(char));

			return *this;
		}

		FORCEINLINE friend XInputStream& operator>>(XInputStream &stream, TChar &value)
		{
			Deserialize(&value, 0, sizeof(TChar));

			return *this;
		}

	private:
		uint8 m_flag;
	};
}

#endif