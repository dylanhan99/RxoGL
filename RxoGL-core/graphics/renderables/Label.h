#pragma once
#include "Renderable2D.h"

namespace rxogl
{
	class Label : public Renderable2D
	{
	private:
		std::string m_Text;
	public:
		Label(std::string text, float x, float y, constants::rxoColor color);
		void Submit(Renderer2D* renderer) const override;
	};
}