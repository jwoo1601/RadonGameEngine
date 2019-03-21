#pragma once

#include "RadonCore.h"

namespace Radon::Render
{
	class RADON_API IRenderable
	{
		virtual void Render(float partialTicks) PURE_VIRTUAL;
	};
}