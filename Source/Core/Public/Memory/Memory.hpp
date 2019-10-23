#pragma once

#include "RadonCore.h"

namespace Radon::Memory
{
	template <typename T>
	FORCEINLINE T* AddPointer(T *ptr, TIndex offset)
	{
		return (T*)(reinterpret_cast<UIntPtr>(ptr) + offset);
	}

	template <typename T>
	FORCEINLINE T* IncrementPointer(T *&ptr, TIndex offset)
	{
		ptr = AddPointer(ptr, offset);

		return ptr;
	}

	template <typename T>
	FORCEINLINE T* SubtractPointer(T *ptr, TIndex offset)
	{
		return (T*)(reinterpret_cast<UIntPtr>(ptr) - offset);
	}

	template <typename T>
	FORCEINLINE T* DecrementPointer(T *&ptr, TIndex offset)
	{
		ptr = SubtractPointer(ptr, offset);

		return ptr;
	}

	template <typename T>
	FORCEINLINE T* AlignForward(T *ptr, uint8 alignment, TIndex offset = 0)
	{
		return (T*)((reinterpret_cast<UIntPtr>(ptr) + static_cast<UIntPtr>(offset) + static_cast<UIntPtr>(alignment - 1)) & static_cast<UIntPtr>(~(alignment - 1)));
	}

	template <typename T>
	FORCEINLINE T* AlignBackward(T *ptr, uint8 alignment, TIndex offset = 0)
	{
		return (T*)((reinterpret_cast<UIntPtr>(ptr) + static_cast<UIntPtr>(offset)) & static_cast<UIntPtr>(~(alignment - 1)));
	}

	// calculates the required padding bytes to forward-align {ptr} in {alignment} bytes
	template <typename T>
	FORCEINLINE uint8 GetForwardAlignmentPadding(T *ptr, uint8 alignment, TIndex offset = 0)
	{
		uint8 padding = alignment - ((reinterpret_cast<UIntPtr>(ptr) + static_cast<UIntPtr>(offset)) & static_cast<UIntPtr>(alignment - 1));
		return padding == alignment ? 0 : padding;
	}

	template <typename E, typename T>
	FORCEINLINE uint8 GetForwardAlignmentPaddingWithHeader(T *ptr, uint8 alignment, TIndex offset = 0)
	{
		if (RADON_ALIGNOF(E) > alignment)
			alignment = RADON_ALIGNOF(E);

		uint8 padding = sizeof(E) + GetForwardAlignmentPadding(AddPointer(ptr, sizeof(E)), alignment, offset);

		return padding;
	}

	// calculates the required padding bytes to backward-align {ptr} in {alignment} bytes
	template <typename T>
	FORCEINLINE uint8 GetBackwardAlignmentPadding(T *ptr, uint8 alignment, TIndex offset = 0)
	{
		uint8 padding = (reinterpret_cast<UIntPtr>(ptr) + static_cast<UIntPtr>(offset)) & static_cast<UIntPtr>(alignment - 1);
		return padding == alignment ? 0 : padding;
	}
}