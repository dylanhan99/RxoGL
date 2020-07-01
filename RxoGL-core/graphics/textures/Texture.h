#pragma once
#include <string>
#include "../../ConstantsRxogl.h"

namespace rxogl
{
	struct TexCoords
	{
		glm::vec2 bl, br, tr, tl;
	};

	class Texture
	{
	protected:
		unsigned int m_RendererID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
		unsigned int m_Width, m_Height, m_BPP;
		TexCoords m_TexCoords;

	public:
		Texture(const std::string& filePath);
		~Texture();

		void Load();
		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

		virtual void Add(std::string textureName, float bl_x, float bl_y, float w, float h) {}; // For TextureSheet

		inline const unsigned int&			GetTexID()		const { return m_RendererID; }
		inline const unsigned int&			GetWidth()		const { return m_Width; }
		inline const unsigned int&			GetHeight()		const { return m_Height; }

		virtual inline const TexCoords&		GetTexCoords(std::string textureName = NULL)	const { return m_TexCoords; }
	};
}