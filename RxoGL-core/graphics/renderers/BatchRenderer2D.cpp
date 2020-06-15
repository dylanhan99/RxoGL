#include "BatchRenderer2D.h"

namespace rxogl
{
	BatchRenderer2D::BatchRenderer2D()
		: m_Buffer(NULL), m_IndexCount(0),
		m_VAO(),
		m_VBO(RENDERER_BUFFER_SIZE)
	{
		rxogl::BufferLayout layout;
		layout.Push<constants::rxoPosition>	(1); // vec4 Pos, 4th element = 1
		layout.Push<constants::rxoColor>	(1); // vec4 Color
		layout.Push<constants::rxoTexCoords>(1); // Texture
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

	void BatchRenderer2D::Submit(const Renderable2D* renderable)
	{
		const glm::vec4&	position	= renderable->GetPosition();
		const glm::vec4&	color		= renderable->GetColor();
		const glm::vec2&	size		= renderable->GetSize();
		const Texture*		texture		= renderable->GetTexture();
		const unsigned int& texID		= texture->GetTexID();
		//if (texture != NULL)
		//	texID = texture->GetTexID();

		unsigned int col = 0;
		float texSlot = 0.f;
		//if (texID > 0)
		if (texture != nullptr)
		{
			bool found = false;
			for (int i = 0; i < m_TextureSlots.size(); i++)
			{
				texSlot = (float)(i + 1);
				found = true;
				break;
			}

			if (!found)
			{
				if (m_TextureSlots.size() >= 32)
				{
					End();
					Flush();
					Begin();
				}
				m_TextureSlots.push_back(texID);
				texSlot = (float)(m_TextureSlots.size() - 1);
			}
		}
		else
		{
			int r = color.x * 255.f;
			int g = color.y * 255.f;
			int b = color.z * 255.f;
			int a = color.w * 255.f;

			col = a << 24 | b << 16 | g << 8 | r;
		}

		m_Buffer->Position = *m_TransformationStackBack * position;
		//m_Buffer->Color = col;
		m_Buffer->Color = color;
		m_Buffer->TexCoords = glm::vec2(0.0f, 0.0f);
		m_Buffer->TexIndex = texSlot;
		m_Buffer++;

		m_Buffer->Position = *m_TransformationStackBack * glm::vec4(position.x + size.x, position.y, position.z, 1);
		m_Buffer->Color = color;
		m_Buffer->TexCoords = glm::vec2(1.0f, 0.0f);
		m_Buffer->TexIndex = texSlot;
		m_Buffer++;

		m_Buffer->Position = *m_TransformationStackBack * glm::vec4(position.x + size.x, position.y + size.y, position.z, 1);
		m_Buffer->Color = color;
		m_Buffer->TexCoords = glm::vec2(1.0f, 1.0f);
		m_Buffer->TexIndex = texSlot;
		m_Buffer++;

		m_Buffer->Position = *m_TransformationStackBack * glm::vec4(position.x, position.y + size.y, position.z, 1);
		m_Buffer->Color = color;
		m_Buffer->TexCoords = glm::vec2(0.0f, 1.0f);
		m_Buffer->TexIndex = texSlot;
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
		for (int i = 0; i < m_TextureSlots.size(); i++)
		{
			GLCall(glActiveTexture(GL_TEXTURE0 + i));
			GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]));
			//GLCall(glBindTextureUnit(i, m_TextureSlots[i]));
		}

		m_VAO.Bind();
		m_IBO->Bind();

		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);

		m_IBO->Unbind();
		m_VAO.Unbind();

		m_IndexCount = 0;
	}
}