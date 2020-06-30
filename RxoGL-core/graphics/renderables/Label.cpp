#include "Label.h"

namespace rxogl
{
	Label::Label(float x, float y, float scale, constants::rxoColor color, std::string text)
		: Renderable2D(), m_Text(text), m_Scale(scale)
	{
		m_Position = constants::rxoPosition(x, y, 0.f, 1);
		m_Color = color;
		m_IsText = true;
	}

	void Label::Submit(Renderer2D* renderer) const
	{
		renderer->SubmitString(this);
	}
}