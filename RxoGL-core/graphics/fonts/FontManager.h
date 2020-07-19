#pragma once
#include "Font.h"

namespace rxogl
{
	class FontManager
	{
	private:
		std::unordered_map<std::string, Font> m_Fonts;
	public:
		FontManager();
		~FontManager();

		void RegisterFont(std::string fontName, std::string filePath);
		inline const Font& GetFont(std::string fontName) const { return m_Fonts.at(fontName); }
	};
}