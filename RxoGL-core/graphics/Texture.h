#pragma once
#include <string>

namespace rxogl
{
	class Texture
	{
	private:
		unsigned int m_RendererID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
		unsigned int m_Width, m_Height, m_BPP;

	public:
		Texture(const std::string& filePath);
		~Texture();

		void Load();
		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

		inline const unsigned int& GetTexID()	const { return m_RendererID; }
		inline const unsigned int& GetWidth()	const { return m_Width; }
		inline const unsigned int& GetHeight()	const { return m_Height; }
	};
}