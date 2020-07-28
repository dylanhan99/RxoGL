#include "Group.h"

namespace rxogl { namespace ecs {

	Group::Group(const glm::mat4& transform)
		: m_TransformationMatrix(transform)
	{

	}

	void Group::Add(Entity2D* renderable)
	{
		m_Renderables.push_back(renderable);
	}

	void Group::Submit(std::shared_ptr<Renderer2D> renderer) const
	{
		renderer->Push(m_TransformationMatrix);

		for (const Entity2D* renderable : m_Renderables)
			renderable->Submit(renderer);

		renderer->Pop();
	}

} }