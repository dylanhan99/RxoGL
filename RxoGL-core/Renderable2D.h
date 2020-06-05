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

		VertexArray* m_VAO;
		VertexBuffer* m_VBO;
		IndexBuffer* m_IBO;
		Shader& m_Shader;

	public:
		Renderable2D(glm::vec3 position, glm::vec2 size, glm::vec4 color, Shader& shader)
			: m_Position(position), m_Size(size), m_Color(color),
			m_Shader(shader)
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
			layout.Push<glm::vec3>(1); // vec3 Pos
			layout.Push<glm::vec4>(1); // vec4 Color
			layout.Push<glm::vec2>(1); // Texture
			layout.Push<float>(1); // Texture ID
			m_VAO->AddBuffer(*m_VBO, layout);


			GLuint indeces[] = { 0, 1, 2, 2, 3, 0 };
			m_IBO = new IndexBuffer(indeces, 6);
		}

		~Renderable2D()
		{
			//m_VAO->~VertexArray();
			//delete m_VAO;
			//m_VBO->~VertexBuffer();
			//delete m_VBO;
		}

		inline const VertexArray* GetVAO() const { return m_VAO; }
		inline const IndexBuffer* GetIBO() const { return m_IBO; }
		
		inline Shader& GetShader() const { return m_Shader; }

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline const glm::vec2& GetSize() const { return m_Size; }
		inline const glm::vec4& GetColor() const { return m_Color; }

	};
}