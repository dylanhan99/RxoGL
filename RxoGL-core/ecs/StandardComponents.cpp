#include "StandardComponents.h"

#include "../graphics/renderers/Renderer2D.h"
#include "../Application.h"

namespace rxogl { namespace ecs {

	Texture::Texture(const std::string& textureName, const std::string& path, float r, float g, float b, float a, bool isTextureSheet)
		: m_TextureDat(NULL), 
		m_TexCoords({ glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f) }),
		m_IsTextureSheet(isTextureSheet),
		m_Color(r, g, b, a)
	{
		if (isTextureSheet)
			m_TextureName = textureName;
		m_TextureDat = Application::GetInstance()->GetTextureManager().AddTexture(path);
	}

	Texture::Texture(float r, float g, float b, float a)
		: m_TextureDat(NULL), 
		m_TexCoords({ glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f) }),
		m_IsTextureSheet(false),
		m_Color(r, g, b, a)
	{
		
	}

	Texture::~Texture()
	{
		
	}

	//void Texture::Submit(std::shared_ptr<Renderer2D> renderer) const
	//{
	//	renderer->Submit(this);
	//}

	//void Texture::Load()
	//{
	//	m_LocalBuffer = utils::LoadTexture(m_FilePath.c_str(), m_Width, m_Height);
	//
	//	GLCall(glGenTextures(1, &m_RendererID));
	//	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	//
	//	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	//	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	//	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	//	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	//
	//	//GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	//	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	//	GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	//	Unbind();
	//}

	void Texture::Bind(unsigned int slot) const
	{
		//GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		//GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

		if(m_TextureDat)
			m_TextureDat->Bind();
	}

	void Texture::Unbind() const
	{
		if (m_TextureDat)
			m_TextureDat->Unbind();
	}

	//bool Texture::HasTexture() const

	Label::Label(float scale, float r, float g, float b, float a, std::string text, std::string fontName)
		: m_Text(text), m_Scale(scale), m_FontName(fontName), m_Color(constants::rxoColor(r, g, b, a))
	{
		//m_Position = constants::rxoPosition(x, y, 0.f, 1);
		//m_Color = color;
		//m_IsText = true;
	}

	//void Label::Submit(std::shared_ptr<Renderer2D> renderer) const
	//{
	//	renderer->Submit(this);
	//}

} }