#pragma once

#include <deque>
#include "Renderer.h"

namespace rxogl
{
	class SimpleRenderer2D : Renderer
	{
	private:
		std::deque<Renderable2D> m_RenderQueue;
	public:
		void Submit(Renderable2D* renderable) override;
		void Flush() override;
	};
}