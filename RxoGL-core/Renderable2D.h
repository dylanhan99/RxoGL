#pragma once

#include <glm/glm.hpp>;
#include "VertexArray.h"
#include "Buffer.h"
#include "graphics/shader.h"

namespace rxogl
{
	class Renderable2D
	{
	protected:
		glm::vec3 m_Position;
		glm::vec2 m_Size;
		glm::vec4 m_Color;

	public:
		Renderable2D(glm::vec3 position, glm::vec2 size, glm::vec4 color)
			: m_Position(position), m_Size(size), m_Color(color)
		{ }

		~Renderable2D()
		{ }

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline const glm::vec2& GetSize() const { return m_Size; }
		inline const glm::vec4& GetColor() const { return m_Color; }

	};
}