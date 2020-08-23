#include "PhysicsManager.h"
//#include "../ecs/StandardComponents.h"
#include "../Application.h"

namespace rxogl
{
	void CollisionManager::Update(float deltatime)
	{
		for (auto spt_EntityA : m_Collidables)
		{
			for (auto spt_EntityB : m_Collidables)
			{
				if (spt_EntityB == spt_EntityA) continue;
				for (auto spt_ColliderA : spt_EntityA->GetColliders())
				{
					for (auto spt_ColliderB : spt_EntityB->GetColliders())
					{
						m_Colliding;
						auto pairA = std::make_pair(spt_ColliderA, spt_ColliderB);
						auto pairB = std::make_pair(spt_ColliderB, spt_ColliderA);
						bool isColliding = spt_ColliderA->ResolveCollision(*spt_ColliderB);
						bool inColliding = m_Colliding.find(pairA) != m_Colliding.end() || m_Colliding.find(pairB) != m_Colliding.end();
						//if (isColliding) 
						//	continue;
						// If isColliding AND  NOT in m_Colliding...
						if (isColliding && !inColliding)// && m_Colliding.find())
						{
							// <Pair, Hash>
							auto collisionPair = m_Colliding.emplace(pairA); // Add to m_Colliding
							if (collisionPair.second)
							{
								spt_ColliderA->OnCollisionEnter(spt_ColliderB);
								spt_ColliderB->OnCollisionEnter(spt_ColliderA);

								std::cout << "ENTER" << std::endl;
							}
						}
					}
				}
			}
		}

		std::vector<std::pair<std::shared_ptr<ecs::ColliderComponent>, std::shared_ptr<ecs::ColliderComponent>>> removePairs;
		for (auto collisionPair : m_Colliding)
		{
			if (!collisionPair.first->ResolveCollision(*collisionPair.second))
			{
				collisionPair.first->OnCollisionExit(collisionPair.second);
				collisionPair.second->OnCollisionExit(collisionPair.first);
				removePairs.push_back(collisionPair);

				std::cout << "EXIT" << std::endl;

				continue;
			}
			collisionPair.first->OnCollisionStay(collisionPair.second);
			collisionPair.second->OnCollisionStay(collisionPair.first);

			std::cout << "STAY" << std::endl;
		}
		for (auto collisionPair : removePairs)
			m_Colliding.erase(collisionPair);

	}

	bool CollisionManager::BOXvsBOX(ecs::BoxCollider2D c1, ecs::BoxCollider2D c2)
	{
		if (c1.m_Max.x < c2.m_Min.x or c1.m_Min.x > c2.m_Max.x) return false;
		if (c1.m_Max.y < c2.m_Min.y or c1.m_Min.y > c2.m_Max.y) return false;

		//std::cout << "Box touch" << std::endl;
		return true;
	}

	bool CollisionManager::CIRCLEvsCIRCLE(ecs::CircleCollider2D c1, ecs::CircleCollider2D c2)
	{
		auto c1Transform = c1.Entity().GetComponent<ecs::Transform>();
		auto c2Transform = c2.Entity().GetComponent<ecs::Transform>();
		float r = c1.m_Radius + c2.m_Radius;
		r *= r;

		//std::cout << "Circle touch\n" << std::endl;
		return r < (pow((c1Transform->x() + c2Transform->x()), 2) + 
					pow((c1Transform->y() + c2Transform->y()), 2));
	}

	bool CollisionManager::BOXvsCIRCLE(ecs::BoxCollider2D c1, ecs::CircleCollider2D c2)
	{
		return false;
	}
}