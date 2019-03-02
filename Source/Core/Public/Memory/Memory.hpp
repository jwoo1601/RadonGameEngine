#pragma once

#include "RadonCore.h"

namespace Radon::Memory
{
	template <typename T>
	FORCEINLINE T* IncrementPointer(T *ptr, size_t offset)
	{
		return (T*)(reinterpret_cast<UIntPtr>(ptr) + offset);
	}

	template <typename T>
	FORCEINLINE T* DecrementPointer(T *ptr, size_t offset)
	{
		return (T*)(reinterpret_cast<UIntPtr>(ptr) - offset);
	}

	template <typename T>
	FORCEINLINE T* AlignForward(T *ptr, uint8 alignment)
	{
		return (T*)((reinterpret_cast<UIntPtr>(ptr) + static_cast<UIntPtr>(alignment - 1)) & static_cast<UIntPtr>(-alignment));
	}

	template <typename T>
	FORCEINLINE T* AlignBackward(T *ptr, uint8 alignment)
	{
		return (T*)(reinterpret_cast<UIntPtr>(ptr) & static_cast<UIntPtr>(-alignment));
	}

	// calculates the required padding bytes to forward-align {ptr} in {alignment} bytes
	template <typename T>
	FORCEINLINE uint8 GetForwardAlignmentPadding(T *ptr, uint8 alignment)
	{
		uint8 padding = alignment - (reinterpret_cast<UIntPtr>(ptr) & static_cast<UIntPtr>(alignment - 1));
		return padding == alignment ? 0 : padding;
	}

	template <typename E, typename T>
	FORCEINLINE uint8 GetForwardAlignmentPaddingWithHeader(T *ptr, uint8 alignment)
	{
		if (alignof(E) > alignment)
			alignment = alignof(E);

		uint8 padding = sizeof(E) + GetForwardAlignmentPadding(IncrementPointer(ptr, sizeof(E)), alignment);

		return padding;
	}

	// calculates the required padding bytes to backward-align {ptr} in {alignment} bytes
	template <typename T>
	FORCEINLINE uint8 GetBackwardAlignmentPadding(T *ptr, uint8 alignment)
	{
		uint8 padding = reinterpret_cast<UIntPtr>(ptr) & static_cast<UIntPtr>(alignment - 1);
		return padding == alignment ? 0 : padding;
	}
}