#include "BatchRenderer2D.h"

namespace rxogl
{
	BatchRenderer2D::BatchRenderer2D()
		: m_VAO(),
		m_VBO(RENDERER_BUFFER_SIZE)
	{
		//Init();
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

	void BatchRenderer2D::Submit(Renderable2D* renderable)
	{

	}

	void BatchRenderer2D::Flush()
	{

	}
}