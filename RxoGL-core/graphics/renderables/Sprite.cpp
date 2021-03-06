#include "Sprite.h"

namespace rxogl
{
	Sprite::Sprite(float x, float y, float z, float width, float height, glm::vec4 color)
		: Entity2D(constants::rxoPosition(x, y, z, 1), glm::vec2(width, height), color, false,
			"")
	{
	}

	Sprite::Sprite(float x, float y, float z, float width, float height, Texture* texture, 
		std::string textureName/*, float bl_x, float bl_y, float w, float h*/)
		: Entity2D(constants::rxoPosition(x, y, z, 1), glm::vec2(width, height), constants::rxoColor(1, 0, 1, 1), false,
			textureName)
	{
		m_Texture = texture;
	}
}