#include "StandardComponents.h"

#include "../graphics/renderers/Renderer2D.h"
#include "../Application.h"

namespace rxogl { namespace ecs {

	Texture::Texture(const std::string& textureName, const std::string& path, float r, float g, float b, float a, bool isTextureSheet)
		: m_TextureDat(NULL), 
		m_TexCoords({ glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f) }),
		m_IsTextureSheet(isTextureSheet),
		m_Color(r, g, b, a)
	{
		if (isTextureSheet)
			m_TextureName = textureName;
		m_TextureDat = Application::GetInstance()->GetTextureManager().AddTexture(path);
	}

	void Collider2D::Init()
	{
		Application::GetInstance()->GetPhysicsManager().GetColliders().push_back(this);
	}

} }