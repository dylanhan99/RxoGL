#include "StaticSprite.h"

namespace rxogl
{
	StaticSprite::StaticSprite(glm::vec3 position, glm::vec2 size, glm::vec4 color, Shader& shader)
		: Renderable2D(position, size, color), m_Shader(shader)
	{
		static const constants::Vertex vertices[]
		{
		constants::Vertex{ glm::vec3(position.x,		  position.y,			position.z), color, glm::vec2(0.0f, 0.0f), 0.0f },
		constants::Vertex{ glm::vec3(position.x + size.x, position.y,			position.z), color, glm::vec2(1.0f, 0.0f), 0.0f },
		constants::Vertex{ glm::vec3(position.x + size.x, position.y + size.y,	position.z), color, glm::vec2(1.0f, 1.0f), 0.0f },
		constants::Vertex{ glm::vec3(position.x,		  position.y + size.y,	position.z), color, glm::vec2(0.0f, 1.0f), 0.0f }
		};

		m_VAO = new VertexArray();
		m_VBO = new VertexBuffer(vertices, sizeof(vertices));
		BufferLayout layout;
		layout.Push<glm::vec3>(1);	// vec3 Pos
		layout.Push<glm::vec4>(1);	// vec4 Color
		layout.Push<glm::vec2>(1);	// Texture
		layout.Push<float>(1);		// Texture ID
		m_VAO->AddBuffer(*m_VBO, layout);


		GLuint indeces[] = { 0, 1, 2, 2, 3, 0 };
		m_IBO = new IndexBuffer(indeces, 6);
	}

	StaticSprite::~StaticSprite()
	{
		delete m_VAO;
		delete m_IBO;
	}
}