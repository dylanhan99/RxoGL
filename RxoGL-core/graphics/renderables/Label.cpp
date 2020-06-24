#include "Label.h"

namespace rxogl
{
	Label::Label(std::string text, float x, float y, constants::rxoColor color)
		: Renderable2D(), m_Text(text)
	{
		m_Position = constants::rxoPosition(x, y, 0.f, 1);
		m_Color = color;
	}

	void Label::Submit(Renderer2D* renderer) const
	{
		renderer->DrawString(m_Text, m_Position, m_Color);
	}
}