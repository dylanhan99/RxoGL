#include "ECS.h"
#include "../graphics/renderers/Renderer2D.h"
#include "../graphics/layers/Layer.h"

namespace rxogl { namespace ecs {

	void Entity::Update()
	{
		for (auto& c : m_Components) c->Update();
		for (auto& c : m_Components) c->Draw(m_Layer->GetRenderer());
	}

	void RenderableComponent::Draw(std::shared_ptr<Renderer2D> renderer) 
	{ 
		renderer->Submit(this); 
	}

} }