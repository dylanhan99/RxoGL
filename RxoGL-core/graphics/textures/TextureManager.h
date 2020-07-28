#pragma once
#include <gl/glew.h>

namespace rxogl
{
	class TextureData
	{
	private:
		unsigned int m_RendererID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
		unsigned int m_Width, m_Height, m_BPP;
	public:
		TextureData(const std::string& path) { Load(); }
		~TextureData()
		{
			if (m_LocalBuffer)
			{
				GLCall(glDeleteTextures(1, &m_RendererID));
				delete m_LocalBuffer;
			}
		}
		void Load()
		{
			m_LocalBuffer = utils::LoadTexture(m_FilePath.c_str(), m_Width, m_Height);

			GLCall(glGenTextures(1, &m_RendererID));
			GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

			//GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, m_LocalBuffer));
			GLCall(glGenerateMipmap(GL_TEXTURE_2D));
			Unbind();
		}
		void Bind(unsigned int slot = 0) const { GLCall(glBindTextureUnit(slot, m_RendererID)); }
		void Unbind() const { GLCall(glBindTexture(GL_TEXTURE_2D, 0)); }
	};

	class TextureManager
	{
	private:
		std::unordered_map<std::string, TextureData> m_Textures;
	public:
		TextureManager() { }
		~TextureManager() { }
	
		const TextureData& AddTexture(std::string path) { m_Textures[path] = newTexture; return GetTexture(path); }
		inline const TextureData& GetTexture(std::string path) const { return m_Textures.at(path); }
	};
}