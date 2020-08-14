#include "StandardComponents.h"

#include "../graphics/renderers/Renderer2D.h"
#include "../Application.h"
#include "../physics/PhysicsManager.h"

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

	bool BoxCollider2D::ResolveCollision(ColliderComponent& other)
	{
		switch (other.GetColliderType()) {
		case ColliderType::BoxCollider2D:
			return PhysicsManager::ResolveCollision<BoxCollider2D, BoxCollider2D>(*this, (BoxCollider2D&)other);
		case ColliderType::CircleCollider2D:
			return PhysicsManager::ResolveCollision<BoxCollider2D, CircleCollider2D>(*this, (CircleCollider2D&)other);
		default:
			return false;
		}
	}


} }