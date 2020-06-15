#include "Sprite.h"

namespace rxogl
{
	//Sprite::Sprite(glm::vec3 position, glm::vec2 size, glm::vec4 color)
	//	: Renderable2D(position, size, color)
	//{

	//}
	Sprite::Sprite(float x, float y, float z, float width, float height, glm::vec4 color)
		: Renderable2D(constants::rxoPosition(x, y, z, 1),
			glm::vec2(width, height),
			color)
	{
	}

	Sprite::Sprite(float x, float y, float z, float width, float height, Texture* texture)
		: Renderable2D(constants::rxoPosition(x, y, z, 1),
			glm::vec2(width, height),
			constants::rxoColor(1, 0, 1, 1))
	{
		m_Texture = texture;
	}
}