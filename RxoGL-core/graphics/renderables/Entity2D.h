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
		
	public:
		Entity2D() {}; //: m_TextureName(""), m_IsText(false) {};
		//Entity2D(std::string textureName)
		//	: m_TextureName(textureName), m_IsText(false)
		//{
		//
		//}

		~Entity2D()
		{ }
	};

} }