#pragma once

#include <glm/glm.hpp>;
#include "../buffers/VertexArray.h"
#include "../buffers/Buffer.h"
#include "../shader.h"
#include "../renderers/Renderer2D.h"
#include "../Texture.h"

namespace rxogl
{
	//class Renderer2D;
	class Renderable2D
	{
	protected:
		constants::rxoPosition m_Position;
		glm::vec2 m_Size;
		constants::rxoColor m_Color;
		Texture* m_Texture;
		float m_IsText;

		Renderable2D() : m_Texture(nullptr), m_IsText(false) {};
	public:
		Renderable2D(constants::rxoPosition position, glm::vec2 size, constants::rxoColor color, bool isText)
			: m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr), m_IsText(isText)
		{ }

		~Renderable2D()
		{ }

		virtual void Submit(Renderer2D* renderer) const
		{
			renderer->Submit(this);
		}

		inline const constants::rxoPosition&	GetPosition()	const { return m_Position; }
		inline const glm::vec2&					GetSize()		const { return m_Size; }
		inline const constants::rxoColor&		GetColor()		const { return m_Color; }
		inline const Texture*					GetTexture()	const { return m_Texture; }
		inline const float&						GetIsText()		const { return m_IsText; }

		virtual const std::string&				GetText()		const { return NULL; }
		virtual const float&					GetScale()		const { return NULL; }
	};
}