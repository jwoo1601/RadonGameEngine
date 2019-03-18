#pragma once

#include "RadonCore.h"

namespace Radon::Memory
{
	template <typename A = VDefaultAllocator, typename = TEnableIf<TIsDerivedFrom<A, IAllocator>>>
	struct TMemoryScope
	{
		// Class Attributes
		CLASS_NOT_COPYABLE(TMemoryScope);

		// Assertions
		static_assert(std::is_default_constructible_v<A>, "{A} must be of kind IAllocator && default constructible!");

	public:
		// Type Definitions
		typedef A AllocatorType;

	public:

		// Constructors
		TMemoryScope(TSize memorySize)
		{
			if (memorySize > 0)
			{
				m_memoryPtr = m_alloc.Allocate(memorySize, 0);
				m_memorySize = memorySize;
			}
		}

		// Destructors
		~TMemoryScope()
		{
			if (m_memoryPtr)
			{
				m_alloc.Deallocate(m_memoryPtr);
			}
		}
		
		// SMemoryScope Interface
		FORCEINLINE void* GetMemoryPtr() const
		{
			return m_memoryPtr;
		}

		FORCEINLINE TSize GetMemorySize() const
		{
			return m_memorySize;
		}

	private:
		AllocatorType	 m_alloc;
		void			*m_memoryPtr;
		TSize			 m_memorySize;
	};
}