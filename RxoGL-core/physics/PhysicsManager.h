#pragma once
#include <unordered_set>
#include <vector>
#include <memory>

#include "../ecs/StandardComponents.h"

namespace rxogl
{
	struct ComponentPairHash
	{
		template <typename T>
		std::size_t operator()(T t) const 
		{
			std::size_t x = t.first->Entity().GetID();
			std::size_t y = t.second->Entity().GetID();
		
			return (x >= y) ? (x * x + x + y) : (y * y + y + x);
		}
	};

	class CollisionManager
	{
	private:
		std::vector<std::shared_ptr<ecs::Entity>> m_Collidables;
		//std::vector<std::shared_ptr<ecs::ColliderComponent>> m_Colliding;
		// unordered_set<ColliderComponent_Pair, PairHash>;
		std::unordered_set<std::pair<std::shared_ptr<ecs::ColliderComponent>, std::shared_ptr<ecs::ColliderComponent>>, ComponentPairHash> m_Colliding;

	public:
		void Update(float deltatime);
		//inline std::vector<ecs::ColliderComponent*>& GetColliders() { return m_Colliders; }
		inline std::vector<std::shared_ptr<ecs::Entity>>& GetCollidables() { return m_Collidables; }
		inline void AddCollidable(std::shared_ptr<ecs::Entity> sPtr) { m_Collidables.push_back(sPtr); }

		template<typename T, typename O>
		static bool ResolveCollision(T c1, O c2)
		{
			//static_assert(false); // this is annoying
			return false;
		}
		template<>
		static bool ResolveCollision(ecs::BoxCollider2D c1, ecs::BoxCollider2D c2)
		{
			return CollisionManager::BOXvsBOX(c1, c2);
		}
		template<>
		static bool ResolveCollision(ecs::CircleCollider2D c1, ecs::CircleCollider2D c2)
		{
			return CollisionManager::CIRCLEvsCIRCLE(c1, c2);
		}
		template<>
		static bool ResolveCollision(ecs::BoxCollider2D c1, ecs::CircleCollider2D c2)
		{
			return CollisionManager::BOXvsCIRCLE(c1, c2);
		}
		template<>
		static bool ResolveCollision(ecs::CircleCollider2D c1, ecs::BoxCollider2D c2)
		{
			return CollisionManager::BOXvsCIRCLE(c2, c1);
		}
	private:
		static bool BOXvsBOX(ecs::BoxCollider2D c1, ecs::BoxCollider2D c2); // Axis Aligned Bounding Boxes (Box)
		static bool CIRCLEvsCIRCLE(ecs::CircleCollider2D c1, ecs::CircleCollider2D c2);
		static bool BOXvsCIRCLE(ecs::BoxCollider2D c1, ecs::CircleCollider2D c2);
	};

	class PhysicsManager
	{
	//private:
	//	std::unordered_map<std::string, std::vector<std::shared_ptr<ecs::Entity>>> m_;
	};
}