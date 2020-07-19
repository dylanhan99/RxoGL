#include "FontManager.h"

namespace rxogl
{
	FontManager::FontManager()
	{

	}

	FontManager::~FontManager()
	{

	}

	void FontManager::RegisterFont(std::string fontName, std::string filePath)
	{
		m_Fonts[fontName] = Font(filePath, 48);
	}
}