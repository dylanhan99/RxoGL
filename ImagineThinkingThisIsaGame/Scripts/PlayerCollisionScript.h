#pragma once
#include "rxogl.h"
#include "ecs/ECS.h"
#include "ecs/StandardComponents.h"
#include "physics/PhysicsManager.h"

namespace Game { namespace Script {

	class PlayerCollisionScript : public rxogl::ecs::NativeScript
	{
	private:
		std::vector<std::shared_ptr<rxogl::ecs::Entity>> m_GroundEntities;
		std::shared_ptr<rxogl::ecs::ColliderComponent> m_ThisCollider;
	public:
		void OnCreate() override 
		{ 
			m_GroundEntities = m_Entity->m_Layer->GetEntitiesTag("ground");
			m_ThisCollider = m_Entity->GetComponent<rxogl::ecs::BoxCollider2D>();
		}
		void OnDestroy() override { }
		void OnUpdate(float deltatime) override 
		{ 
			for (auto e : m_GroundEntities)
			{
				if (m_ThisCollider->ResolveCollision(*e->GetComponent<rxogl::ecs::BoxCollider2D>()))
				{
					auto transform = m_Entity->GetComponent<rxogl::ecs::Transform>();
					auto groundTransform = e->GetComponent<rxogl::ecs::Transform>();
					auto newPos = glm::vec3(transform->x(), groundTransform->y() + groundTransform->GetSize().y, transform->z());
					m_Entity->GetComponent<rxogl::ecs::Transform>()->SetPos(newPos);
				}
			}
		}
	};

} }