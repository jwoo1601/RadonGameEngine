#pragma once

#include "RadonCore.h"

#include "Renderable.h"

namespace Radon::Render
{
	typedef int HRender;

	struct SRenderTargetInfo
	{
		HRender renderId;

		SRenderTargetInfo() = delete;
	};

	class RADONCORE_API VRenderer
	{
	public:

		// Renderer Public Interface
		virtual HRender CreateRenderTarget();
		virtual void AttachRenderTarget(std::shared_ptr<IRenderable> pTarget);
		virtual void DetachRenderTarget(HRender renderId);

		// Renderer Abstract Interface
		virtual void Render(float partialTicks) PURE_VIRTUAL;

	protected:

	};
}