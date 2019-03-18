// Copyright 2019 Simon Kim All Rights Reserved.

#pragma once

#include "RadonCore.h"

namespace Radon
{
	class RADONCORE_API VWorld
	{
	public:

		// Constructors
		VWorld();

		// Destructors
		~VWorld();

		virtual void* CreateObject(size_t size);
		virtual void DeleteObject(void *objPtr);

		template <typename T>
		T* SpawnObject();
		template <typename T>
		void DestroyObject(T *objPtr);

		TObjectIterator GetObjectIterator() const;
	};
}