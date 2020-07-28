#pragma once
#include "Entity2D.h"

namespace rxogl
{
	class Label : public Entity2D
	{
	private:
		std::string m_Text;
		float m_Scale;
		std::string m_FontName;
	public:
		Label(float x, float y, float scale, constants::rxoColor color, std::string text, std::string fontName);
		void Submit(std::shared_ptr<Renderer2D> renderer) const override;

		inline void EditText(std::string newText) { m_Text = newText; }

		inline const std::string&		GetText()	const override	{ return m_Text; }
		inline const float&				GetScale()	const override	{ return m_Scale; }
	};
}