#pragma once

#include <glm/glm.hpp>;
#include "../buffers/VertexArray.h"
#include "../buffers/Buffer.h"
#include "../shader.h"
#include "../renderers/Renderer2D.h"
#include "../textures/TextureSheet.h"

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
		std::string m_TextureName; // TextureName should be parsed in as 0/NULL/"" if NOT a sprite sheet.
		float m_IsText; // is font or not

		Renderable2D() : m_Texture(nullptr), m_IsText(false) {};
	public:
		Renderable2D(constants::rxoPosition position, glm::vec2 size, constants::rxoColor color, bool isText, 
			std::string textureName/*, float bl_x, float bl_y, float w, float h*/)
			: m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr), m_IsText(isText),
			m_TextureName(textureName) 
		{ 

		}

		~Renderable2D()
		{ }

		virtual void Submit(Renderer2D* renderer) const
		{
			renderer->Submit(this);
		}

		inline const constants::rxoPosition&	GetPosition()		const { return m_Position; }
		inline const glm::vec2&					GetSize()			const { return m_Size; }
		inline const constants::rxoColor&		GetColor()			const { return m_Color; }
		inline const Texture*					GetTexture()		const { return m_Texture; }
		inline const std::string&				GetTextureName()	const { return m_TextureName; }
		inline const float&						GetIsText()			const { return m_IsText; }

		virtual const std::string&				GetText()			const { return NULL; }
		virtual const float&					GetScale()			const { return NULL; }
	};
}