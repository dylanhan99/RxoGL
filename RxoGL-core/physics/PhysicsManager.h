#pragma once
#include <unordered_set>
#include <vector>
#include <memory>

namespace rxogl
{
	namespace ecs
	{
		class ColliderComponent;
		class BoxCollider2D;
		class CircleCollider2D;
	}

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
		void Resolve(ecs::ColliderComponent& colA, ecs::ColliderComponent& colB);

		inline std::vector<ecs::ColliderComponent*>& GetColliders() { return m_Colliders; }
	private:
		bool BOXvsBOX(ecs::BoxCollider2D c1, ecs::BoxCollider2D c2); // Axis Aligned Bounding Boxes (Box)
		bool CIRCLEvsCIRCLE(ecs::CircleCollider2D c1, ecs::CircleCollider2D c2);
	};
}