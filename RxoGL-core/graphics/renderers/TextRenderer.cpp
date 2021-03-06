#include "TextRenderer.h"

namespace rxogl
{
	TextRenderer::TextRenderer()
		: Renderer2D(),
		m_Buffer(NULL), m_IndexCount(0), m_VAO(), m_VBO(RENDERER_BUFFER_SIZE)
	{
		rxogl::BufferLayout layout;
		layout.Push<constants::rxoPosition>(1);		// vec4 Pos, 4th element = 1
		layout.Push<constants::rxoColor>(1);		// vec4 Color
		layout.Push<constants::rxoTexCoords>(1);	// Texture
		layout.Push<float>(1);						// Texture ID

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

	TextRenderer::~TextRenderer()
	{
		delete(m_IBO);
		m_VAO.~VertexArray();
		m_VBO.~VertexBuffer();
	}

	void TextRenderer::Begin()
	{
		m_VBO.Bind();
		m_Buffer = (constants::TextVertex*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	/*
	void TextRenderer::Submit(const Renderable2D* renderable)
	{
		const constants::rxoPosition& position = renderable->GetPosition();
		const constants::rxoColor& color = renderable->GetColor();
		const glm::vec2& size = renderable->GetSize();
		const Texture* texture = renderable->GetTexture();
		const TexCoords* texCoords = new TexCoords{ glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f) };
		const unsigned int& texID = texture->GetTexID();
		//const float& isText = renderable->GetIsText();

		unsigned int col = 0;
		float texSlot = 0.f;
		if (texture)
		{
			bool found = false;
			for (int i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots[i] == texID)
				{
					texSlot = (float)(i + 1);
					found = true;
					break;
				}
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

			delete texCoords;
			texCoords = &texture->GetTexCoords(renderable->GetTextureName());
		}

		m_Buffer->Position = *m_TransformationStackBack * position;
		m_Buffer->Color = color;
		m_Buffer->TexCoords = texCoords->bl;
		m_Buffer->TexIndex = texSlot;
		//m_Buffer->IsText = isText;
		m_Buffer++;

		m_Buffer->Position = *m_TransformationStackBack * glm::vec4(position.x + size.x, position.y, position.z, 1);
		m_Buffer->Color = color;
		m_Buffer->TexCoords = texCoords->br;
		m_Buffer->TexIndex = texSlot;
		//m_Buffer->IsText = isText;
		m_Buffer++;

		m_Buffer->Position = *m_TransformationStackBack * glm::vec4(position.x + size.x, position.y + size.y, position.z, 1);
		m_Buffer->Color = color;
		m_Buffer->TexCoords = texCoords->tr;
		m_Buffer->TexIndex = texSlot;
		//m_Buffer->IsText = isText;
		m_Buffer++;

		m_Buffer->Position = *m_TransformationStackBack * glm::vec4(position.x, position.y + size.y, position.z, 1);
		m_Buffer->Color = color;
		m_Buffer->TexCoords = texCoords->tl;
		m_Buffer->TexIndex = texSlot;
		//m_Buffer->IsText = isText;
		m_Buffer++;

		m_IndexCount += 6;
	}
	*/

	// This could easily be an if else in Submit funciton but 
	// i split to make it clearer to me for now
	void TextRenderer::Submit(const Renderable2D* renderable)
	{
		const std::string& text = renderable->GetText();
		float x_Offset = renderable->GetPosition().x;

		for (const char& c : text)
		{
			const constants::rxoPosition& position = renderable->GetPosition();
			const constants::rxoColor& color = renderable->GetColor();
			//const glm::vec2&				size		= renderable->GetSize(); // Size should have a defualt null value or something
			const constants::Character& ch = m_Font.GetCharacter(c);
			const unsigned int& texID = ch.TextureID;
			const float& scale = renderable->GetScale();
			//const bool& isText = renderable->GetIsText();

			float xpos = x_Offset + ch.Bearing.x * scale;
			float ypos = position.y - (ch.Size.y - ch.Bearing.y) * scale;
			float w = ch.Size.x * scale;
			float h = ch.Size.y * scale;

			float texSlot = 0.f;
			bool found = false;
			for (int i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots[i] == texID)
				{
					texSlot = (float)(i + 1);
					found = true;
					break;
				}
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

			m_Buffer->Position = *m_TransformationStackBack * constants::rxoPosition(xpos, ypos, 0, 1);
			m_Buffer->Color = color;
			m_Buffer->TexCoords = glm::vec2(0.0f, 1.0f);
			m_Buffer->TexIndex = texSlot;
			//m_Buffer->IsText = isText;
			m_Buffer++;

			m_Buffer->Position = *m_TransformationStackBack * constants::rxoPosition(xpos + w, ypos, 0, 1);
			m_Buffer->Color = color;
			m_Buffer->TexCoords = glm::vec2(1.0f, 1.0f);
			m_Buffer->TexIndex = texSlot;
			//m_Buffer->IsText = isText;
			m_Buffer++;

			m_Buffer->Position = *m_TransformationStackBack * constants::rxoPosition(xpos + w, ypos + h, 0, 1);
			m_Buffer->Color = color;
			m_Buffer->TexCoords = glm::vec2(1.0f, 0.0f);
			m_Buffer->TexIndex = texSlot;
			//m_Buffer->IsText = isText;
			m_Buffer++;

			m_Buffer->Position = *m_TransformationStackBack * constants::rxoPosition(xpos, ypos + h, 0, 1);
			m_Buffer->Color = color;
			m_Buffer->TexCoords = glm::vec2(0.0f, 0.0f);
			m_Buffer->TexIndex = texSlot;
			//m_Buffer->IsText = isText;
			m_Buffer++;

			m_IndexCount += 6;
			x_Offset += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
		}
	}

	void TextRenderer::End()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		m_VBO.Unbind();
	}

	void TextRenderer::Flush()
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