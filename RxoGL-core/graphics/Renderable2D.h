#pragma once

#include <glm/glm.hpp>;
#include "buffers/VertexArray.h"
#include "buffers/Buffer.h"
#include "shader.h"

namespace rxogl
{
	class Renderable2D
	{
	protected:
		constants::rxoPosition m_Position;
		glm::vec2 m_Size;
		constants::rxoColor m_Color;

	public:
		Renderable2D(constants::rxoPosition position, glm::vec2 size, constants::rxoColor color)
			: m_Position(position), m_Size(size), m_Color(color)
		{ }

		~Renderable2D()
		{ }

		inline const constants::rxoPosition& GetPosition() const { return m_Position; }
		inline const glm::vec2&				 GetSize() const { return m_Size; }
		inline const constants::rxoColor&	 GetColor() const { return m_Color; }

	};
}