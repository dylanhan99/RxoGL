#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

#include <typeinfo>

namespace rxogl { 
	class Renderer2D;
	class Layer;
	namespace ecs {
		
	class Component;
	class Entity;

	constexpr std::size_t max_components = 32;
	using ComponentID = std::size_t;
	using ComponentBitSet = std::bitset<max_components>;
	using ComponentArray = std::array<std::shared_ptr<Component>, max_components>;

	inline ComponentID GetComponentTypeID()
	{
		static ComponentID lastID = 0;
		return lastID++;
	}

	template <typename T> inline ComponentID GetComponentTypeID() noexcept
	{
		static ComponentID typeID = GetComponentTypeID();
		return typeID;
	}

	class Component
	{
	private:
		friend class Entity;
	protected:
		Entity* m_Entity; // Reference to the entity it is attached to
	public:
		virtual ~Component() {}
		virtual void Init() {}
		virtual void Update(float deltatime) {}
		virtual void Draw() {}

		//virtual void OnCollisionEnter(std::shared_ptr<ColliderComponent> other) { }
		//virtual void OnCollisionStay(std::shared_ptr<ColliderComponent> other)	{ }
		//virtual void OnCollisionExit(std::shared_ptr<ColliderComponent> other)	{ }

		inline const Entity& Entity() const { return *m_Entity; }
	};

	class RenderableComponent : public Component
	{
	protected:
		std::string m_TextureName; // TextureName should be parsed in as 0/NULL/"" if NOT a sprite sheet.
		float		m_IsText; // is font or not
		// This should be used only for stuff to be rendered to screen.
		// E.g. Texture, Label, etc.
		//virtual void Submit(std::shared_ptr<Renderer2D> renderer) const {}
	public:
		void Draw() override;
		inline const float&			IsText()			const { return m_IsText; }
		inline const std::string&	GetTextureName()	const { return m_TextureName; }
	};

	class PhysicsComponent : public Component
	{
		void Update(float deltatime) override;
	};

	class ColliderComponent : public Component
	{
	protected:
		enum class ColliderType
		{
			None = 0,
			PolygonCollider2D,
			BoxCollider2D,
			CircleCollider2D
		};
		ColliderType m_ColliderType;
	public:
		//void Init() override

		virtual bool ResolveCollision(const ColliderComponent& other)
		{ return false; }

		const ColliderType& GetColliderType() const { return m_ColliderType; }
		//void OnCollisionEnter(std::shared_ptr<ColliderComponent> other) override;
		//void OnCollisionStay(std::shared_ptr<ColliderComponent> other)	override;
		//void OnCollisionExit(std::shared_ptr<ColliderComponent> other)	override;
	};
	
	class Entity
	{
	private:
		using EntityID = size_t;
		inline EntityID NewEntityID()
		{
			static EntityID lastID = 0;
			return lastID++;
		}

		EntityID m_EntID = NewEntityID();
		bool m_Active = true;
		std::vector<std::shared_ptr<Component>> m_Components;
		std::vector<std::shared_ptr<ColliderComponent>> m_Collidables;

		ComponentArray m_ComponentArray;
		ComponentBitSet m_ComponentBitSet;
	public:
		Layer* m_Layer;
		virtual void Update(float deltatime);
		virtual void Draw();
		bool IsActive() const { return m_Active; }
		void SetActive(bool state) { m_Active = state; }

		template <typename T> 
		bool HasComponent() const
		{
			return m_ComponentBitSet[GetComponentTypeID<T>()];
		}

		template <typename T, typename... TArgs>
		void AddComponent(TArgs&&... mArgs)//std::shared_ptr<Component> AddComponent(TArgs&&... mArgs)
		{
			T* c(new T(std::forward<TArgs>(mArgs)...));
			c->m_Entity = this;
			std::shared_ptr<Component> sPtr{ c };

			m_ComponentArray[GetComponentTypeID<T>()] = sPtr;
			m_ComponentBitSet[GetComponentTypeID<T>()] = true;
			//m_Collidables.emplace_back(sPtr);

			sPtr->Init();
			//m_Components.emplace_back(std::move(sPtr)); pls use this in future
			m_Components.push_back(sPtr);
			//return sPtr;
		}

		template <typename T> 
		std::shared_ptr<T> GetComponent() const
		{
			//auto ptr(m_Components[GetComponentTypeID<T>()]);
			//return *static_cast<T*>(ptr);
			//auto sPtr = m_Components[GetComponentTypeID<T>()];
			//return sPtr;
			return std::static_pointer_cast<T>(m_ComponentArray[GetComponentTypeID<T>()]);
			//return *static_cast<T*>(m_Components[GetComponentTypeID<T>()]);
		}
		
		inline const std::vector<std::shared_ptr<ColliderComponent>>& GetColliders() const { return m_Collidables; }
		inline void AddCollider(std::shared_ptr<ColliderComponent> col) { m_Collidables.push_back(col); }
		inline const EntityID& GetID() const { return m_EntID; }
		//void OnCollisionEnter(std::shared_ptr<ColliderComponent> other)
		//{ for(const auto& c : m_CollidableComponents) c->OnCollisionEnter(other); }
		//void OnCollisionStay(std::shared_ptr<ColliderComponent> other)
		//{ for(const auto& c : m_CollidableComponents) c->OnCollisionStay(other); }
		//void OnCollisionExit(std::shared_ptr<ColliderComponent> other)
		//{ for(const auto& c : m_CollidableComponents) c->OnCollisionExit(other); }
	//private:
		//void AddCollider(std::shared_ptr<ColliderComponent> col); // Add to PhysicsManager's collider vector
	};

	class EntityManager
	{
	private:
		std::vector<std::shared_ptr<Entity>> m_Entities;
	public:
		void Update(float deltatime)
		{ for (auto& e : m_Entities) e->Update(deltatime); }
		void Draw()
		{ for (auto& e : m_Entities) e->Draw(); }

		void Refresh()
		{
			m_Entities.erase(std::remove_if(std::begin(m_Entities), std::end(m_Entities), [](const std::shared_ptr<Entity>& entity)
				{
					return !entity->IsActive();
				}),
				std::end(m_Entities));
		}

		void AddEntity(Entity* e);
		//{
		//	//Entity* e = new Entity();
		//	std::shared_ptr<Entity> sPtr{ e };
		//	m_Entities.emplace_back(std::move(sPtr));
		//	Application::GetInstance()->GetPhysicsManager().AddCollidable(sPtr);
		//	//return *e;
		//}
	};

} }