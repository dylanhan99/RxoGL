#pragma once

#include "../renderables/Renderable2D.h"

namespace rxogl
{
	class Group : public Renderable2D
	{
	private:
		std::vector<Renderable2D*> m_Renderables;
		glm::mat4 m_TransformationMatrix;

	public:
		Group(const glm::mat4& transform);
		void Add(Renderable2D* renderable);
		void Submit(Renderer2D* renderer) const override;
	};
}