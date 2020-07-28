#include "Label.h"
#include "../../vendor/imgui/imgui_impl_glfw.h"
#include "../../vendor/imgui/imgui_impl_opengl3.h"

namespace rxogl
{
	Label::Label(float x, float y, float scale, constants::rxoColor color, std::string text, std::string fontName)
		: Entity2D(), m_Text(text), m_Scale(scale), m_FontName(fontName)
	{
		m_Position = constants::rxoPosition(x, y, 0.f, 1);
		m_Color = color;
		m_IsText = true;
	}

	void Label::Submit(std::shared_ptr<Renderer2D> renderer) const
	{
		renderer->SubmitString(this, m_FontName);
	}
}