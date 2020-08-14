#include "PhysicsManager.h"
//#include "../ecs/StandardComponents.h"
#include "../Application.h"

namespace rxogl
{
	void PhysicsManager::Update(float deltatime)
	{
		for (auto spt_ColliderA : m_Colliders)
		{
			for (auto spt_ColliderB : m_Colliders)
			{
				if (spt_ColliderB == spt_ColliderA) continue;
				spt_ColliderA->ResolveCollision(*spt_ColliderB);
			}
		}
	}

	bool PhysicsManager::BOXvsBOX(ecs::BoxCollider2D c1, ecs::BoxCollider2D c2)
	{
		if (c1.m_Max.x < c2.m_Min.x or c1.m_Min.x > c2.m_Max.x) return false;
		if (c1.m_Max.y < c2.m_Min.y or c1.m_Min.y > c2.m_Max.y) return false;

		std::cout << "Box touch" << std::endl;
		return true;
	}

	bool PhysicsManager::CIRCLEvsCIRCLE(ecs::CircleCollider2D c1, ecs::CircleCollider2D c2)
	{
		auto& c1Transform = c1.Entity().GetComponent<ecs::Transform>();
		auto& c2Transform = c2.Entity().GetComponent<ecs::Transform>();
		float r = c1.m_Radius + c2.m_Radius;
		r *= r;

		std::cout << "Circle touch\n" << std::endl;
		return r < (pow((c1Transform.x() + c2Transform.x()), 2) + 
					pow((c1Transform.y() + c2Transform.y()), 2));
	}

	bool PhysicsManager::BOXvsCIRCLE(ecs::BoxCollider2D c1, ecs::CircleCollider2D c2)
	{
		return false;
	}
}