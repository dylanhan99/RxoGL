#include "BatchRenderer2D.h"

namespace rxogl
{
	BatchRenderer2D::BatchRenderer2D()
		: m_Buffer(NULL), m_IndexCount(0),
		m_VAO(),
		m_VBO(RENDERER_BUFFER_SIZE)
	{
		rxogl::BufferLayout layout;
		layout.Push<glm::vec3>(1); // vec3 Pos
		layout.Push<glm::vec4>(1); // vec4 Color
		layout.Push<glm::vec2>(1); // Texture
		layout.Push<float>(1); // Texture ID
		m_VAO.AddBuffer(m_VBO, layout);

		unsigned int indeces[RENDERER_INDICES_SIZE];
		unsigned int offset = 0;
		for (size_t i = 0; i < RENDERER_INDICES_SIZE; i += 6)
		{
			indeces[i + 0] = 0 + offset;
			indeces[i + 1] = 1 + offset;
			indeces[i + 2] = 2 + offset;

			indeces[i + 3] = 2 + offset;
			indeces[i + 4] = 3 + offset;
			indeces[i + 5] = 0 + offset;

			offset += 4;
		}

		m_IBO = new IndexBuffer(indeces, RENDERER_INDICES_SIZE);
	}

	BatchRenderer2D::~BatchRenderer2D()
	{
		delete(m_IBO);
		m_VAO.~VertexArray();
		m_VBO.~VertexBuffer();
	}

	void BatchRenderer2D::Begin()
	{
		m_VBO.Bind();
		m_Buffer = (constants::Vertex*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void BatchRenderer2D::Submit(Renderable2D* renderable)
	{
		const glm::vec3& position = renderable->GetPosition();
		const glm::vec4& color = renderable->GetColor();
		const glm::vec2& size = renderable->GetSize();

		m_Buffer->Position = position;
		m_Buffer->Color = color;
		m_Buffer->TexCoords = glm::vec2(0.0f, 0.0f);
		m_Buffer->TexIndex = 0.0f;
		m_Buffer++;

		m_Buffer->Position = glm::vec3(position.x + size.x, position.y, position.z);
		m_Buffer->Color = color;
		m_Buffer->TexCoords = glm::vec2(1.0f, 0.0f);
		m_Buffer->TexIndex = 0.0f;
		m_Buffer++;

		m_Buffer->Position = glm::vec3(position.x + size.x, position.y + size.y, position.z);
		m_Buffer->Color = color;
		m_Buffer->TexCoords = glm::vec2(1.0f, 1.0f);
		m_Buffer->TexIndex = 0.0f;
		m_Buffer++;

		m_Buffer->Position = glm::vec3(position.x, position.y + size.y, position.z);
		m_Buffer->Color = color;
		m_Buffer->TexCoords = glm::vec2(0.0f, 1.0f);
		m_Buffer->TexIndex = 0.0f;
		m_Buffer++;

		m_IndexCount += 6;
	}

	void BatchRenderer2D::End()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		m_VBO.Unbind();
	}

	void BatchRenderer2D::Flush()
	{
		m_VAO.Bind();
		m_IBO->Bind();

		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);

		m_IBO->Unbind();
		m_VAO.Unbind();

		m_IndexCount = 0;
	}
}