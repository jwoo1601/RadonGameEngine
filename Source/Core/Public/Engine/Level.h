// Copyright 2019 Simon Kim All Rights Reserved.

#pragma once

#include "RadonCore.h"
#include "Object.h"
#include "World.h"

namespace Radon
{
	class RADON_API VLevel : public VObject
	{
		INHERITS_FROM(VObject);
	public:

		// Constructors
		VLevel();

		// Destructors
		~VLevel();
	};
}