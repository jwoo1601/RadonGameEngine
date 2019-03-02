#pragma once

#include <cstdio>
#include <chrono>

#include "RadonCore.h"
#include "RadonMemory.h"
#include "Platform/RadonPlatform.h"

using namespace Radon;
using namespace Radon::Memory;

class PointerTestUnit
{
public:

	void UnitTest()
	{
		SMemoryScope scope(1024);
		VLinearAllocator alloc(scope.GetMemoryPtr(), scope.GetMemorySize());

		auto intArray = AllocateNewArray<int>(alloc, 10);
		auto doubleArray = AllocateNewArray<double>(alloc, 50);
		auto charArray = AllocateNewArray<char>(alloc, 100);
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
};