#pragma once

#include "../renderables/Entity2D.h"

namespace rxogl { namespace ecs {

	class Group : public Entity2D
	{
	private:
		std::vector<Entity2D*> m_Renderables;
		glm::mat4 m_TransformationMatrix;

	public:
		Group(const glm::mat4& transform);
		void Add(Entity2D* renderable);
		//void Submit(std::shared_ptr<Renderer2D> renderer) const override;
	};

} }