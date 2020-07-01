#include "TextureSheet.h"

namespace rxogl
{
	TextureSheet::TextureSheet(std::string filePath)
		: Texture(filePath)
	{

	}

	void TextureSheet::Add(std::string texName, float bl_x, float bl_y, float w, float h)
	{
		bl_x	/=	 m_Height;
		bl_y	/=	 m_Width;
		w		/=	 m_Height;
		h		/=	 m_Width;
		m_TexCoordsCache[texName] = TexCoords
		{	
			glm::vec2(bl_x		, bl_y		), // bl
			glm::vec2(bl_x + w	, bl_y		), // br
			glm::vec2(bl_x + w	, bl_y + h	), // tr
			glm::vec2(bl_x		, bl_y + h	)  // tl 
		};
	}
}