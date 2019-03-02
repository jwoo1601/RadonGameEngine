#pragma once

#include "RadonCore.h"

namespace Radon::Render
{
	class INTERFACE IRenderable
	{
		virtual void Render(float partialTicks) PURE_VIRTUAL;
	};
}