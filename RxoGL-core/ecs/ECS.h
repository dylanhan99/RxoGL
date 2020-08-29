#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <functional>

#include <typeinfo>
#include "../native-scripting/NativeScriptManager.h"

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

		std::shared_ptr<void> m_SptThis;
	public:
		virtual ~Component() {}
		virtual void Init() {}
		virtual void Update(float deltatime) {}
		virtual void Draw() {}
		
		//std::function<void()> BindScript = []() {  };


		inline const Entity& Entity() const { return *m_Entity; }
	};

	class RenderableComponent : public Component
	{
	protected:
		std::string m_TextureName;	// TextureName should be parsed in as 0/NULL/"" if NOT a sprite sheet.
		float		m_IsText;		// is font or not
		std::size_t m_NumSides;		// For polygon rendering.
		// This should be used only for stuff to be rendered to screen.
		// E.g. Texture, Label, etc.
		//virtual void Submit(std::shared_ptr<Renderer2D> renderer) const {}
	public:
		RenderableComponent(std::size_t numSides = 4) : m_NumSides(numSides) { }

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
		virtual void OnCollisionEnter(std::shared_ptr<ColliderComponent> other) { }// override;
		virtual void OnCollisionStay(std::shared_ptr<ColliderComponent> other) { }//	override;
		virtual void OnCollisionExit(std::shared_ptr<ColliderComponent> other) { }//	override;
	};

	class NativeScriptComponent : public Component
	{
	private:
		void* m_Instance = nullptr;
	public:
		std::function<void()> InstantiateFunction;
		std::function<void()> DestroyInstanceFunction;
		std::function<void()> OnCreateFunction;
		std::function<void()> OnDestroyFunction;
		std::function<void(float)> OnUpdateFunction;

		//template<typename T>
		void* GetInstance()
		{
			return m_Instance;
		}

		template<typename T, typename... TArgs>
		void Bind(TArgs&&... mArgs)
		{
			InstantiateFunction		= [&]() { 
				if (!m_Instance)
				{
					m_Instance = new T(std::forward<TArgs>(mArgs)...);
					((T*)m_Instance)->m_Entity = m_Entity;
				}
			};
			DestroyInstanceFunction = [&]() { delete (T*)m_Instance; m_Instance = nullptr; };
		
			OnCreateFunction  = [&]() { ((T*)m_Instance)->OnCreate(); };
			OnDestroyFunction = [&]() { ((T*)m_Instance)->OnDestroy(); };
			OnUpdateFunction  = [&](float deltatime) { ((T*)m_Instance)->OnUpdate(deltatime); };

			//((T*)m_Instance)->m_Entity = m_Entity;
			NativeScriptManager::GetInstance()->AddScript(std::static_pointer_cast<NativeScriptComponent>(m_SptThis));
		}
	};

	class NativeScript
	{
	private:
		friend class NativeScriptComponent;
	protected:
		Entity* m_Entity;
	public:
		virtual void OnCreate() = 0;
		virtual void OnDestroy() = 0;
		virtual void OnUpdate(float deltatime) = 0;
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
		std::shared_ptr<T> AddComponent(TArgs&&... mArgs)//std::shared_ptr<Component> AddComponent(TArgs&&... mArgs)
		{
			T* c(new T(std::forward<TArgs>(mArgs)...));
			std::shared_ptr<T> sPtr{ c };
			sPtr->m_Entity = this;
			sPtr->m_SptThis = sPtr;

			m_ComponentArray[GetComponentTypeID<T>()] = sPtr;
			m_ComponentBitSet[GetComponentTypeID<T>()] = true;
			//m_Collidables.emplace_back(sPtr);

			sPtr->Init();
			//m_Components.emplace_back(std::move(sPtr)); pls use this in future
			m_Components.push_back(sPtr);
			return sPtr;
		}

		template <typename T> 
		std::shared_ptr<T> GetComponent() const
		{
			//auto ptr(m_Components[GetComponentTypeID<T>()]);
			//return *static_cast<T*>(ptr);
			//auto sPtr = m_Components[GetComponentTypeID<T>()];
			//return sPtr;
			return std::static_pointer_cast<T>(m_ComponentArray[GetComponentTypeID<T>()]);
		}
		
		inline const std::vector<std::shared_ptr<ColliderComponent>>& GetColliders() const { return m_Collidables; }
		inline void AddCollider(std::shared_ptr<ColliderComponent> col) { m_Collidables.push_back(col); }
		inline const EntityID& GetID() const { return m_EntID; }
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

		std::shared_ptr<Entity> AddEntity(Entity* e);
		//{
		//	//Entity* e = new Entity();
		//	std::shared_ptr<Entity> sPtr{ e };
		//	m_Entities.emplace_back(std::move(sPtr));
		//	Application::GetInstance()->GetPhysicsManager().AddCollidable(sPtr);
		//	//return *e;
		//}
	};

} }