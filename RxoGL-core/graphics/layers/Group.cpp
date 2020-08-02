#include "Group.h"
#include "Layer.h"

namespace rxogl { namespace ecs {

	Group::Group(const glm::mat4& transform)
		: m_TransformationMatrix(transform)
	{

	}

	void Group::Add(ecs::Entity* entity)
	{
		entity->m_Layer = m_Layer;
		m_EntityManager.AddEntity(entity);
	}

	void Group::Draw()
	{
		m_Layer->GetRenderer()->Push(m_TransformationMatrix);
		m_EntityManager.Draw();
		m_Layer->GetRenderer()->Pop();
	}


	//void Group::Submit(std::shared_ptr<Renderer2D> renderer) const
	//{
	//	renderer->Push(m_TransformationMatrix);
	//
	//	for (const Entity2D* renderable : m_Renderables)
	//		renderable->Submit(renderer);
	//
	//	renderer->Pop();
	//}

} }