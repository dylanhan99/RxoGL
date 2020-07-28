#pragma once

#include <glm/glm.hpp>;
#include "../buffers/VertexArray.h"
#include "../buffers/Buffer.h"
#include "../shader.h"
#include "../renderers/Renderer2D.h"
#include "../textures/TextureSheet.h"

#include "../../ecs/ECS.h"

namespace rxogl { namespace ecs {

	class Entity2D : public Entity
	{
	protected:
		//constants::rxoPosition m_Position;
		//glm::vec2 m_Size;
		//constants::rxoColor m_Color;
		//Texture* m_Texture;
		std::string m_TextureName; // TextureName should be parsed in as 0/NULL/"" if NOT a sprite sheet.
		float m_IsText; // is font or not

		Entity2D() : m_TextureName(""), m_IsText(false) {};
	public:
		//Entity2D(constants::rxoPosition position, glm::vec2 size, constants::rxoColor color, bool isText,
		//	std::string textureName)
		//	: m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr), m_IsText(isText),
		//	m_TextureName(textureName)
		//{ }

		Entity2D(std::string textureName)
			: m_TextureName(textureName), m_IsText(false)
		{

		}

		~Entity2D()
		{ }

		virtual void Submit(std::shared_ptr<Renderer2D> renderer) const
		{
			renderer->Submit(this);
		}

		//inline const constants::rxoPosition&	GetPosition()		const { return m_Position; }
		//inline const glm::vec2&					GetSize()			const { return m_Size; }
		//inline const constants::rxoColor&		GetColor()			const { return m_Color; }
		//inline const Texture*					GetTexture()		const { return m_Texture; }
		inline const std::string&				GetTextureName()	const override { return m_TextureName; }
		inline const float&						GetIsText()			const { return m_IsText; }

		//virtual const std::string&				GetText()			const { return NULL; }
		//virtual const float&					GetScale()			const { return NULL; }
	};

} }