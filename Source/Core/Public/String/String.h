// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_STRING_H
#define RADON_STRING_H

#include "RadonCoreMinimal.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

#include "Array.h"

namespace Radon::String
{
	template <typename CharType>
	class TStringBase
	{
	public:
		TSize Length() const;
		TSize MaxLength() const;

		bool Contains(CharType ch);
		bool Contains(const CharType* rawString);
		bool Contains(const TStringBase<CharType>& string);

		TIndex IndexOf(CharType ch);
		TIndex LastIndexOf(CharType ch);

	private:
		TArray<CharType> m_chars;
	};

#include "String.inl"

	class RADON_API XString : public TStringBase<TChar>
	{
	public:

		XString();
		XString(const TChar *rawString);
		XString(const XString &rhs);
		XString(XString &&rhs);

		/* String Queries */
		TSize Length() const;
		TSize Capacity() const;

		bool IsEmpty() const;

		bool Contains(TChar ch);
		bool Contains(const TChar *rawString);
		bool Contains(const XString &str);

		TIndex IndexOf(TChar ch);

		int32 HashCode() const;

		/* Data Management Methods */
		void Shrink();
		void Reserve(TSize numChars);
		void Clear();

		void ToLowerCase();
		void ToUpperCase();

		void Replace(const TChar *pattern, const TChar *replacement);
		void Trim();
		
		XString&& Substring(TIndex startIndex, TIndex endIndex);

		/* Conversion Mehtods */
		SName            ToName() const;
		XUnicodeString&& ToUTF8() const;
		TChar*           ToCharArray();
		const TChar*     ToCharArray() const;

		/* Operators */
		XString& operator=(const TChar *rawString);
		XString& operator=(SName name);
		XString& operator=(const XString &rhs);
		XString& operator=(XString &&rhs);

		TChar& operator[](TIndex index);
		TChar operator[](TIndex index) const;

		XString& operator+=(TChar ch);
		XString& operator+=(const TChar *rawString);
		XString& operator+=(SName name);
		XString& operator+=(const XString &rhs);



		bool operator==(const TChar *rawString) const;
		bool operator==(SName name) const;
		bool operator==(const XString &rhs) const;

		bool operator!=(const TChar *rawString) const;
		bool operator!=(SName name) const;
		bool operator!=(const XString &rhs) const;

		bool operator>(const TChar *rawString) const;
		bool operator>(SName name) const;
		bool operator>(const XString &rhs) const;

		bool operator>=(const TChar *rawString) const;
		bool operator>=(SName name) const;
		bool operator>=(const XString &rhs) const;

		bool operator<(const TChar *rawString) const;
		bool operator<(SName name) const;
		bool operator<(const XString &rhs) const;

		bool operator<=(const TChar *rawString) const;
		bool operator<=(SName name) const;
		bool operator<=(const XString &rhs) const;

	private:
		TArray<TChar> charArray;
	};

	class RADON_API XUnicodeString
	{

	};
}

#endif