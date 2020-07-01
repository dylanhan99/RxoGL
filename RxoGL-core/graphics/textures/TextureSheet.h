#pragma once
#include "Texture.h"
#include <unordered_map>

namespace rxogl
{
	class TextureSheet : public Texture
	{
	private:
		std::unordered_map<std::string, TexCoords> m_TexCoordsCache;
	public:
		TextureSheet(const std::string filePath);
		void Add(std::string textureName, float bl_x, float bl_y, float w, float h) override;

		inline const TexCoords& GetTexCoords(std::string textureName) const override { return m_TexCoordsCache.at(textureName); }
	};
}