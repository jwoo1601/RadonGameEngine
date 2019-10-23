// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_WORLD_H
#define RADON_WORLD_H

#if COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

#include "RadonCore.h"

namespace Radon
{
	class RADON_API VWorld
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

	private:

		MANAGED
		(
			THashMap<SName, XGameObject> GameObjects,
		)
	};
}

#endif