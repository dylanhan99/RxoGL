#pragma once
#include "Renderable2D.h"

namespace rxogl {
	class Sprite : public Renderable2D
	{
	public:
		Sprite(glm::vec3 position, glm::vec2 size, glm::vec4 color);
	};
}