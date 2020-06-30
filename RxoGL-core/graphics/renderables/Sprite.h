#pragma once
#include "Renderable2D.h"

namespace rxogl {
	class Sprite : public Renderable2D
	{
	public:
		Sprite(float x, float y, float z, float width, float height, glm::vec4 color);
		Sprite(float x, float y, float z, float width, float height, Texture* texture);
	};
}