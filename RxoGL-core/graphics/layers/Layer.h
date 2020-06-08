#pragma once
#include "../Renderer.h"
#include "../Renderable2D.h"

namespace rxogl
{
	class Layer
	{
	protected:
		Renderer* m_Renderer;
		Shader* m_Shader;
		std::vector<Renderable2D*> m_Renderables;
		glm::mat4 m_ProjectionMatrix;

		Layer(Renderer* renderer, Shader* shader, glm::mat4 matrix);
	public:
		virtual ~Layer();
		virtual void Add(Renderable2D* renderable);
		virtual void Render();
	};
}