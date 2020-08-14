#pragma once
#include <unordered_set>
#include <vector>
#include <memory>

#include "../ecs/StandardComponents.h"

namespace rxogl
{
	//namespace ecs
	//{
	//	class ColliderComponent;
	//	class BoxCollider2D;
	//	class CircleCollider2D;
	//}

	//struct ComponentPairHash
	//{
	//	// To parse in an std::pair here
	//	// ComponentPairHash(test); 
	//	//where test = pair<shared_ptr<ColliderComponent>, shared_ptr<ColliderComponent>>
	//	template <typename T>
	//	std::size_t operator()(T t) const 
	//	{
	//		std::size_t x = t.first->Entity()->GetID();
	//		std::size_t y = t.second->Entity()->GetID();
	//
	//		return (x >= y) ? (x * x + x + y) : (y * y + y + x);
	//	}
	//};

	class PhysicsManager
	{
	private:
		std::vector<ecs::ColliderComponent*> m_Colliders;
	public:
		void Update(float deltatime);
		inline std::vector<ecs::ColliderComponent*>& GetColliders() { return m_Colliders; }

		template<typename T, typename O>
		static bool ResolveCollision(T c1, O c2)
		{
			//static_assert(false); // this is annoying
			return false;
		}
		template<>
		static bool ResolveCollision(ecs::BoxCollider2D c1, ecs::BoxCollider2D c2)
		{
			return PhysicsManager::BOXvsBOX(c1, c2);
		}
		template<>
		static bool ResolveCollision(ecs::CircleCollider2D c1, ecs::CircleCollider2D c2)
		{
			return PhysicsManager::CIRCLEvsCIRCLE(c1, c2);
		}
		template<>
		static bool ResolveCollision(ecs::BoxCollider2D c1, ecs::CircleCollider2D c2)
		{
			return PhysicsManager::BOXvsCIRCLE(c1, c2);
		}
		template<>
		static bool ResolveCollision(ecs::CircleCollider2D c1, ecs::BoxCollider2D c2)
		{
			return PhysicsManager::BOXvsCIRCLE(c2, c1);
		}
	private:
		static bool BOXvsBOX(ecs::BoxCollider2D c1, ecs::BoxCollider2D c2); // Axis Aligned Bounding Boxes (Box)
		static bool CIRCLEvsCIRCLE(ecs::CircleCollider2D c1, ecs::CircleCollider2D c2);
		static bool BOXvsCIRCLE(ecs::BoxCollider2D c1, ecs::CircleCollider2D c2);
	};
}