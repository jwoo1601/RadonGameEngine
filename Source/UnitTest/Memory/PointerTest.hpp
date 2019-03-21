// Copyright 2019 Simon Kim All Rights Reserved.

#pragma once

#include <cstdio>
#include <chrono>
#include <iostream>

#include "RadonCore.h"
//#include "RadonMemory.h"

#include "StaticString.h"
#include "StaticConverter.h"

#include "catch.hpp"

using namespace Radon;
//using namespace Radon::Memory;
using namespace Radon::Static;

class PointerTestUnit
{
public:

	void Test33()
	{
/*		constexpr TStaticString<4> BB = TEXT("SDFS");
		constexpr TStaticString<7> SDF = TEXT("DSFSSDF");
		constexpr auto KK = TStaticStringBuilder<'a', 'b', 'c'>::MakeStaticString();
		constexpr auto S1 = MakeStringLiteral(TEXT("AB"));
		constexpr auto S2 = MakeStringLiteral(TEXT("CD"));
		constexpr auto R = S1 + S2; */

		constexpr auto CC = StaticItoa32<-242423422>();
	}

	class A
	{
		bool operator ==(const A &a) const
		{
			return true;
		}
	};

	template <template <class, class> typename D, typename E, typename F>
	class A2
	{
	public:
		D<E, F> d;
		E e;
		F f;
	};

	template <typename B, typename C>
	class A1
	{
	public:

		typedef A1<B, C> MyType;
		typedef A2<A1, B, C> NewType;
	};

	void UnitTest()
	{
	/*	TMemoryScope scope(1024);
		VLinearAllocator alloc(scope.GetMemoryPtr(), scope.GetMemorySize());

		auto intArray = AllocateNewArray<int>(alloc, 10);
		auto doubleArray = AllocateNewArray<double>(alloc, 50);
		auto charArray = AllocateNewArray<char>(alloc, 100);

		int i;
		volatile const int* const pp = &i;
		int &pp2 = i;
		//Test<int**&>();

		int* p3;
		//Test2(&i);

		int *ppp;
		int *& a = ppp;

		//constexpr bool bb = TIsEqualComparable<int&>;

		constexpr bool sss = TIsDerivedFrom<VLinearAllocator, VLinearAllocator>;
		A1<int, long>::NewType C;
		 */

		Test33();
	}

	const void* ConvertPointers(const void *ptr, uint8 val)
	{
		const UIntPtr ptr1 = reinterpret_cast<const UIntPtr>(ptr);
//		const UIntPtr ptr2 = static_cast<const UIntPtr>(ptr); -- error

//		const UIntPtr ptr3 = reinterpret_cast<const UIntPtr>(val); -- error
		const UIntPtr ptr4 = static_cast<const UIntPtr>(val);

		return reinterpret_cast<const void*>(ptr1);
	}

	template <typename T>
	const T* ConvertPointers2(const T *ptr, uint8 val)
	{
		return reinterpret_cast<const T*>(reinterpret_cast<const UIntPtr>(ptr) + 1);
	}

	void MemoryTest()
	{

	}
};