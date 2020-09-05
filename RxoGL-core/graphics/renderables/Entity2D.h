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
	public:
		Entity2D(std::string tag = "") : Entity(tag) {};

		~Entity2D()
		{ }
	};

} }