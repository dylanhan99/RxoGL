#include "ECS.h"
#include "../graphics/renderers/Renderer2D.h"
#include "../graphics/layers/Layer.h"
#include "../Application.h"

namespace rxogl { namespace ecs {

	void Entity::Update(float deltatime)
	{
		for (auto& c : m_Components) c->Update(deltatime);
	}

	void Entity::Draw()
	{
		for (auto& c : m_Components) c->Draw();
	}

	//void Entity::AddCollider(std::shared_ptr<ColliderComponent> col)
	//{
	//	Application::GetInstance()->GetPhysicsManager().GetColliders().push_back(col);
	//}


	void RenderableComponent::Draw()
	{ 
		m_Entity->m_Layer->GetRenderer()->Submit(this);
	}

	void PhysicsComponent::Update(float deltatime)
	{
		//Application::GetInstance()->GetPhysicsManager().
	}

	void EntityManager::AddEntity(Entity* e)
	{
		//Entity* e = new Entity();
		std::shared_ptr<Entity> sPtr{ e };
		//m_Entities.emplace_back(std::move(sPtr)); pls use this in future
		m_Entities.push_back(sPtr);
		Application::GetInstance()->GetCollisionManager().AddCollidable(sPtr);
		//return *e;
	}

} }