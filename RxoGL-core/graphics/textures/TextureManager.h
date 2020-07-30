#pragma once
#include "../../ConstantsRxogl.h"
#include "../../utils/LoadImage.h"

namespace rxogl
{
	struct TextureData
	{
		unsigned int m_RendererID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
		unsigned int m_Width, m_Height, m_BPP;
	
		TextureData(const std::string& path) : m_FilePath(path) { Load(); }
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
		std::unordered_map<std::string, std::shared_ptr<TextureData>> m_Textures;
	public:
		TextureManager() { }
		~TextureManager() { }
	
		std::shared_ptr<TextureData> AddTexture(std::string path)
		{ 
			m_Textures[path] = std::make_shared<TextureData>(path); 
			return GetTexture(path); 
		}
		inline std::shared_ptr<TextureData> GetTexture(std::string path) const { return m_Textures.at(path); }
	};
}