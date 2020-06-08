#pragma once

#include <deque>
#include "Renderer.h"
#include "StaticSprite.h"

namespace rxogl
{
	class SimpleRenderer2D : Renderer
	{
	private:
		std::deque<StaticSprite*> m_RenderQueue;
	public:
		void Submit(const Renderable2D* renderable) override;
		void Flush() override;
	};
}