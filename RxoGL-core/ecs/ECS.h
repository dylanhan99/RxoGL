#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

namespace rxogl { 
	class Renderer2D;
	class Layer;
	namespace ecs {
		
	class Component;
	class Entity;

	constexpr std::size_t max_components = 32;
	using ComponentID = std::size_t;
	using ComponentBitSet = std::bitset<max_components>;
	using ComponentArray = std::array<Component*, max_components>;

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
		virtual void Init() {}
		virtual void Update() {}
		virtual void Draw(std::shared_ptr<Renderer2D> renderer) {}

		virtual ~Component() {}
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
		void Draw(std::shared_ptr<Renderer2D> renderer) override;// { renderer->Submit(this); }
		inline const float&			IsText()			const { return m_IsText; }
		inline const std::string&	GetTextureName()	const { return m_TextureName; }
	};
	
	class Entity
	{
	private:
		bool m_Active = true;
		std::vector<std::unique_ptr<Component>> m_Components;

		ComponentArray m_ComponentArray;
		ComponentBitSet m_ComponentBitSet;

	public:
		Layer* m_Layer;
		virtual void Update();
		virtual void Draw();
		bool IsActive() const { return m_Active; }
		void SetActive(bool state) { m_Active = state; }

		template <typename T> bool HasComponent() const
		{
			return m_ComponentBitSet[GetComponentTypeID<T>()];
		}

		template <typename T, typename... TArgs>
		T& AddComponent(TArgs&&... mArgs)
		{
			T* c(new T(std::forward<TArgs>(mArgs)...));
			c->m_Entity = this;
			std::unique_ptr<Component> uPtr{ c };
			m_Components.emplace_back(std::move(uPtr));

			m_ComponentArray[GetComponentTypeID<T>()] = c;
			m_ComponentBitSet[GetComponentTypeID<T>()] = true;

			c->Init();
			return *c;
		}

		template <typename T> T& GetComponent() const
		{
			auto ptr(m_ComponentArray[GetComponentTypeID<T>()]);
			return *static_cast<T*>(ptr);
		}
	};

	class EntityManager
	{
	private:
		std::vector<std::shared_ptr<Entity>> m_Entities;
	public:
		void Update()
		{
			for (auto& e : m_Entities) e->Update();
		}

		void Draw()
		{
			for (auto& e : m_Entities) e->Draw();
		}

		void Refresh()
		{
			m_Entities.erase(std::remove_if(std::begin(m_Entities), std::end(m_Entities), [](const std::shared_ptr<Entity>& entity)
				{
					return !entity->IsActive();
				}),
				std::end(m_Entities));
		}

		void AddEntity(Entity* e)
		{
			//Entity* e = new Entity();
			std::shared_ptr<Entity> uPtr{ e };
			m_Entities.emplace_back(std::move(uPtr));
			//return *e;
		}
	};

} }