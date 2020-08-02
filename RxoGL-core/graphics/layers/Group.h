#pragma once

#include "../renderables/Entity2D.h"

namespace rxogl { namespace ecs {

	class Group : public Entity2D
	{
	private:
		ecs::EntityManager m_EntityManager;
		glm::mat4 m_TransformationMatrix;

	public:
		Group(const glm::mat4& transform);
		void Add(ecs::Entity* entity);

		void Update() override
		{
			m_EntityManager.Update();
		}
		void Draw() override;
	};

} }