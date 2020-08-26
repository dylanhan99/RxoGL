#include "Group.h"
#include "Layer.h"

namespace rxogl { namespace ecs {

	Group::Group(const glm::mat4& transform)
		: m_TransformationMatrix(transform)
	{ }

	void Group::Add(ecs::Entity* entity)
	{
		m_EntityManager.AddEntity(entity)->m_Layer = m_Layer;
	}

	void Group::Draw()
	{
		m_Layer->GetRenderer()->Push(m_TransformationMatrix);
		m_EntityManager.Draw();
		m_Layer->GetRenderer()->Pop();
	}

} }