#pragma once
#include "../../ecs/StandardComponents.h"

namespace rxogl
{
	struct TextureData
	{

	};
	class TextureManager
	{
	private:
		std::unordered_map<std::string, ecs::Texture> m_Textures;
	public:
		TextureManager() { }
		~TextureManager() { }
	
		void AddTexture(std::string path, ecs::Texture newTexture) { m_Textures[path] = newTexture; }
		inline const ecs::Texture& GetTexture(std::string path) const { return m_Textures.at(path); }
	};
}