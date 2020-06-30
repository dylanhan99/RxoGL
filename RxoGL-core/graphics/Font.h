#pragma once
#include "../vendor/FreeType/FreeType-gl.h"
#include "../ConstantsRxogl.h"
#include <unordered_map>

namespace rxogl
{
	class Font
	{
	private:
		std::string m_FilePath;
		unsigned int m_FontSize;
		std::unordered_map<char, constants::Character> m_Characters;

		void Setup();
	public:
		Font();
		Font(std::string path, unsigned int fontSize);

		inline const constants::Character& GetCharacter(const char& c) const { return m_Characters.at(c); }
	};
}