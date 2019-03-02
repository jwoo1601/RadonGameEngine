#pragma once

#include "RadonCore.h"

namespace Radon::Memory
{
	template <typename A = VDefaultAllocator>
	struct SMemoryScope
	{
		// Class Attributes
		CLASS_NOT_COPYABLE(SMemoryScope);

		// Assertions
		static_assert(std::is_base_of_v<IAllocator, A> && std::is_default_constructible_v<A>, "{A} must be of kind IAllocator && default constructible!");

		// Type Definitions
		typedef A AllocatorType;

	public:

		// Constructors
		SMemoryScope(size_t memorySize)
		{
			if (memorySize > 0)
			{
				m_memoryPtr = m_alloc.Allocate(memorySize, 0);
				m_memorySize = memorySize;
			}
		}

		// Destructors
		~SMemoryScope()
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

		FORCEINLINE size_t GetMemorySize() const
		{
			return m_memorySize;
		}

	private:
		AllocatorType	 m_alloc;
		void			*m_memoryPtr;
		size_t			 m_memorySize;
	};
}