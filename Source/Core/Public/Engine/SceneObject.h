// Copyright 2019 Simon Kim All Rights Reserved.

#pragma once

#include "RadonCore.h"
#include "Object.h"
#include "Level.h"

namespace Radon
{
	// Objects that can be placed into a {VLevel}
	// NOTE: this is under direct management of {VLevel}
	class RADON_API VSceneObject : public VObject
	{
		INHERITS_FROM(VObject)

	public:

		// Constructors
		VSceneObject();

		// Destructors
		~VSceneObject();

		virtual VLevel* GetLevel() const;
	};
}