#pragma once

#include <deque>
#include "Renderer2D.h"
#include "StaticSprite.h"

namespace rxogl
{
	class SimpleRenderer2D : Renderer2D
	{
	private:
		std::deque<StaticSprite*> m_RenderQueue;
	public:
		void Submit(const Renderable2D* renderable) override;
		void Flush() override;
	};
}