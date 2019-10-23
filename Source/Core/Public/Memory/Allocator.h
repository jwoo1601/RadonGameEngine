// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_ALLOCATOR_H
#define RADON_ALLOCATOR_H

//#include "RadonCoreMinimal.h"

//#include "Name.h"
//#include "OutputStream.h"

namespace Radon::Memory
{
	using namespace String;
	using namespace Serialization;

	class RADON_API IAllocator
	{
	public:

		virtual ~IAllocator() { }

		/* IAllocator Interface */
		// allocates new memory space of {size} (in words) with {alignment}
		virtual void* Allocate(TSize size, uint8 alignment, TIndex offset, int32 flag) = 0;

		// deallocates the memory space {ptr}
		// NOTE: may not be available in certain child classes
		virtual void Deallocate(void *ptr) = 0;
	};

	class RADON_API XDefaultAllocator final : public IAllocator
	{
		INHERITS_FROM(IAllocator)

	public:

		/* IAllocator Interface */

		virtual void* Allocate(TSize size, uint8 alignment, TIndex offset, int32 flag) override;
		virtual void Deallocate(void *ptr) override;
	};

	struct RADON_API SAllocatorInitializer
	{
		SAllocatorInitializer();
		SAllocatorInitializer(void *pBase, TSize capacity, TSize reservedSize = 0);
#if RADON_ENABLE_MEMORY_PROFILE
		SAllocatorInitializer(SName profileName, void *pBase, TSize capacity, TSize reservedSize = 0);

		FORCEINLINE SName GetProfileName() const
		{
			return m_profileName;
		}
#endif

		FORCEINLINE void* GetBase() const
		{
			return m_pBase;
		}

		FORCEINLINE TSize GetCapacity() const
		{
			return m_capacity;
		}

		FORCEINLINE TSize GetReservedSize() const
		{
			return m_reservedSize;
		}

	private:
#if RADON_ENABLE_MEMORY_PROFILE
		SName m_profileName;
#endif
		void *m_pBase;
		TSize m_capacity;
		TSize m_reservedSize;
	};

	class RADON_API XBaseAllocator : public IAllocator
	{
		INHERITS_FROM(IAllocator)

	public:

		XBaseAllocator();
		explicit XBaseAllocator(const SAllocatorInitializer &initializer);

		virtual ~XBaseAllocator();

#if RADON_ENABLE_MEMORY_PROFILE
		virtual void PrintMemorySnapshot(XOutputStream &stream) const;
#endif

		FORCEINLINE void* GetBase() const
		{
			return m_pBase;
		}

		FORCEINLINE TSize GetTotalMemorySize() const
		{
			return m_totalMemorySize;
		}

		FORCEINLINE TSize GetUsedMemorySize() const
		{
			return m_usedMemorySize;
		}

		FORCEINLINE TSize GetAvailableMemorySize() const
		{
			return m_totalMemorySize - m_usedMemorySize;
		}

		FORCEINLINE TSize GetNumAllocations() const
		{
			return m_numAllocations;
		}

	protected:
#if RADON_ENABLE_MEMORY_PROFILE
		SName m_profileName;
#endif
		void *m_pBase;
		TSize m_totalMemorySize;
		TSize m_usedMemorySize;
		TSize m_numAllocations;
	};

	class RADON_API XManagedAllocator : public XBaseAllocator
	{
		INHERITS_FROM(XBaseAllocator)

	public:

		virtual void HandleMemoryShortage();

	private:
		class XMemoryManager &m_manager;
	};

	
	// allocates newn memory space for an object of T
	// NOTE: this function does not call the constructor
	template <typename T>
	FORCEINLINE T* AllocateNew(IAllocator &alloc, TIndex offset = 0, int32 flag = 0)
	{
		return (T*)alloc.Allocate(sizeof(T), RADON_ALIGNOF(T), offset, flag);
	}

	// allocates new memory space for an array of objects of T with {size}
	// NOTE: this function does not call the constructor of the elements
	template <typename T>
	T* AllocateNewArray(IAllocator &arrayAlloc, TSize size, TIndex offset = 0, int32 flag = 0)
	{
		RADON_ASSERT(size > 0)

		// sets the size of the array header as that of an element so that we can align the memory in a nice way
		uint8 arrayHeaderSize = sizeof(TSize) / sizeof(T);
		if constexpr (sizeof(TSize) % sizeof(T) != 0)
		{
			arrayHeaderSize++;
		}

		// makes the size of the array stored in the preceding bytes of the elements
		// | size | arr[0] | arr[1] | arr[2] | ... |
		T *arr = ((T*)arrayAlloc.Allocate(sizeof(T) * (arrayHeaderSize + size), RADON_ALIGNOF(T), offset, flag)) + arrayHeaderSize;
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
		return new (alloc.Allocate(sizeof(T), RADON_ALIGNOF(T))) T(std::forward(args...));
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

	template <typename T>
	class TCheckedPtr
	{
	public:

		FORCEINLINE TCheckedPtr(T *ptr) : m_ptr(ptr)
		{
			RADON_ASSERT(ptr);
		}

		FORCEINLINE T* operator->()
		{
#if RADON_ENABLE_MEMORY_PROFILE
			RADON_ASSERT(allocator.GetCurrentCycle() == m_cycle);
#endif
			return m_ptr;
		}

	private:
#if RADON_ENABLE_MEMORY_PROFILE
		const IAllocator &allocator;
		uint32 m_cycle;
#endif
		T *m_ptr;
	};

#if RADON_ENABLE_MEMORY_PROFILE
	class RADON_API XMemoryProfiler
	{
	public:

	private:
		static TLinkedList<const IAllocator&> m_profiledAllocatorList;
	}
#endif
}

#endif