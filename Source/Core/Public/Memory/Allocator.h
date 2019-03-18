#pragma once

#include "RadonCore.h"

namespace Radon::Memory
{
	class RADONCORE_API INTERFACE IAllocator
	{
	public:

		/* IAllocator Interface */
		// allocates new memory space of {size} (in words) with {alignment}
		virtual void* Allocate(TSize size, uint8 alignment, TIndex offset, int32 flag) = 0;

		// deallocates the memory space {ptr}
		// NOTE: may not be available in certain child classes
		virtual void Deallocate(void *ptr) = 0;
	};

	class RADONCORE_API VDefaultAllocator : public IAllocator
	{
		INHERITS_FROM(IAllocator)

	public:

		/* IAllocator Interface*/

		virtual void* Allocate(TSize size, uint8 alignment, TIndex offset, int32 flag) override;
		virtual void Deallocate(void *ptr) override;
	};

	class VMemorySpace;

	class RADONCORE_API VBaseAllocator : public IAllocator
	{
		INHERITS_FROM(IAllocator)

	public:

		VBaseAllocator();
		explicit VBaseAllocator(const VMemorySpace &memorySpace);

		virtual ~VBaseAllocator();


		/* VBaseAllocator Interface */

		FORCEINLINE void* GetBasePtr() const
		{
			return m_basePtr;
		}

		FORCEINLINE size_t GetTotalMemorySize() const
		{
			return m_totalMemorySize;
		}

		FORCEINLINE size_t GetUsedMemorySize() const
		{
			return m_usedMemorySize;
		}

		FORCEINLINE size_t GetAvailableMemorySize() const
		{
			return m_totalMemorySize - m_usedMemorySize;
		}

		FORCEINLINE size_t GetNumAllocations() const
		{
			return m_numAllocations;
		}

	protected:
#if RADON_ENABLE_PROFILE
		SName m_profileName;
#endif
		void *m_basePtr;
		size_t m_totalMemorySize;
		size_t m_usedMemorySize;
		size_t m_numAllocations;
	};

	
	// allocates newn memory space for an object of T
	// NOTE: this function does not call the constructor
	template <typename T>
	FORCEINLINE T* AllocateNew(IAllocator &alloc, TIndex offset = 0, int32 flag = 0)
	{
		return (T*)alloc.Allocate(sizeof(T), ALIGN_OF(T), offset, flag);
	}

	// allocates new memory space for an array of objects of T with {size}
	// NOTE: this function does not call the constructor of the elements
	template <typename T>
	T* AllocateNewArray(IAllocator &arrayAlloc, TSize size, TIndex offset = 0, int32 flag = 0)
	{
		// size > 0

		// sets the size of the array header as that of an element so that we can align the memory in a nice way
		uint8 arrayHeaderSize = sizeof(TSize) / sizeof(T);
		if constexpr (sizeof(TSize) % sizeof(T) != 0)
		{
			arrayHeaderSize++;
		}

		// makes the size of the array stored in the preceding bytes of the elements
		// | size | arr[0] | arr[1] | arr[2] | ... |
		T *arr = ((T*)arrayAlloc.Allocate(sizeof(T) * (arrayHeaderSize + size), ALIGN_OF(T), offset, flag)) + arrayHeaderSize;
		// stores the size of the array
		*(((TSize *)arr) - 1) = size;

		return arr;
	}

	// deallocates the memory space of {ptr}
	// NOTE: this function does not call the destructor
	template <typename T>
	FORCEINLINE void Deallocate(IAllocator &alloc, T *ptr)
	{
		if (ptr)
		{
			alloc.Deallocate(*ptr);
		}
	}

	// deallocates the memory space of {*ptrPtr} and sets {*ptrPtr} to nullptr
	// NOTE: this function does not call the destructor
	template <typename T>
	FORCEINLINE void DeallocateAndReset(IAllocator &alloc, T **ptrPtr)
	{
		if (ptrPtr)
		{
			Deallocate(alloc, *ptrPtr);
			*ptrPtr = nullptr;
		}
	}

	// deallocates the entire memory space of {arr}
	// NOTE: this function does not call the destructor of the elements
	template <typename T>
	FORCEINLINE void DeallocateArray(IAllocator &arrayAlloc, T *arr)
	{
		if (arr)
		{
			constexpr uint8 arrayHeaderSize = sizeof(TSize) / sizeof(T);
			if (sizeof(TSize) % sizeof(T) != 0)
			{
				arrayHeaderSize++;
			}

			arrayAlloc.Deallocate(arr - arrayHeaderSize);
		}
	}

	// constructs an object of T by allocating new memory space
	// NOTE: this function calls the constructor of newly created object
	// NOTE: this function does not allow to specify the offset and flag for this allocation
	template <typename T, typename... Args>
	FORCEINLINE T* ConstructNew(IAllocator &alloc, Args &&...args)
	{
		return new (alloc.Allocate(sizeof(T), alignof(T))) T(std::forward(args...));
	}


	// constructs an array of objects of T with size by allocating new memory space
	// NOTE: this function calls the constructor of each element
	template <typename T>
	FORCEINLINE T* ConstructNewArray(IAllocator &arrayAlloc, TSize size, TIndex offset = 0, int32 flag = 0)
	{
		T *arr = AllocateNewArray(arrayAlloc, size, offset, flag);

		for (TSize i = 0; i < size; i++)
		{
			// NOTE: the new operator with the address of the memory as a parameter only calls the constructor
			// In other words, this call does not allocate new memory space
			new (&arr[i]) T;
		}

		return arr;
	}

	// destructs an object by deallocating the memory space of {objPtr}
	// NOTE: There's no need for {objPtr} to be of kind {VObject}
	template <typename T>
	FORCEINLINE void Destruct(IAllocator &alloc, T *objPtr)
	{
		objPtr->~T();
		alloc.Deallocate(objPtr);
	}

	// destructs an object by deallocating the memory space of {*objPtrPtr} and sets {*objPtrPtr} to nullptr
	// NOTE: There's no need for {*objPtrPtr} to be of kind {VObject}
	template <typename T>
	FORCEINLINE void DestructAndReset(IAllocator &alloc, T **objPtrPtr)
	{
		if (objPtrPtr)
		{
			Destruct(alloc, *objPtrPtr);
			*objPtrPtr = nullptr;
		}
	}

	// destructs an object array by deallocating the entire memory space of {arr}
	// NOTE: There's no need for the elements of {arr} to be of kind {VObject}
	template <typename T>
	FORCEINLINE void DestructArray(IAllocator &arrayAlloc, T *arr)
	{
		if (arr)
		{
			TSize size = *(((TSize*)arr) - 1);

			// should be i = size ?
			for (TSize i = 0; i < size; i++)
			{
				arr[i].~T();
			}

			DeallocateArray(arrayAlloc, arr);
		}
	}

}