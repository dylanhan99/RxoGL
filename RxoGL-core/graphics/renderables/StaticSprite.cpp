#include "StaticSprite.h"

namespace rxogl
{
	StaticSprite::StaticSprite(float x, float y, float z, float width, float height, glm::vec4 color, Shader& shader)
		: Renderable2D(constants::rxoPosition(x, y, z, 1), 
						glm::vec2(width, height), 
						color,
						false), 
			m_Shader(shader)
	{
			static const constants::Vertex vertices[]
			{
			constants::Vertex{ constants::rxoPosition(x,		 y,			 z, 1), color, glm::vec2(0.0f, 0.0f), 0.0f },
			constants::Vertex{ constants::rxoPosition(x + width, y,			 z, 1), color, glm::vec2(1.0f, 0.0f), 0.0f },
			constants::Vertex{ constants::rxoPosition(x + width, y + height, z, 1), color, glm::vec2(1.0f, 1.0f), 0.0f },
			constants::Vertex{ constants::rxoPosition(x,		 y + height, z, 1), color, glm::vec2(0.0f, 1.0f), 0.0f }
			};

			m_VAO = new VertexArray();
			m_VBO = new VertexBuffer(vertices, sizeof(vertices));
			BufferLayout layout;
			layout.Push<constants::rxoPosition>	(1);	// vec4 Pos
			layout.Push<constants::rxoColor>	(1);	// vec4 Color
			layout.Push<constants::rxoTexCoords>(1);	// Texture
			layout.Push<float>(1);		// Texture ID
			m_VAO->AddBuffer(*m_VBO, layout);


			GLuint indeces[] = { 0, 1, 2, 2, 3, 0 };
			m_IBO = new IndexBuffer(indeces, 6);
	}

	StaticSprite::~StaticSprite()
	{
		m_VAO->~VertexArray();
		m_VBO->~VertexBuffer();
		m_IBO->~IndexBuffer();
		delete m_VAO;
		delete m_VBO;
		delete m_IBO;
	}
}