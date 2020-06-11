#pragma once
#include "../Renderer2D.h"
#include "../Renderable2D.h"

namespace rxogl
{
	class Layer
	{
	protected:
		Renderer2D* m_Renderer;
		Shader* m_Shader;
		std::vector<Renderable2D*> m_Renderables;
		glm::mat4 m_ProjectionMatrix;

		Layer(Renderer2D* renderer, Shader* shader, glm::mat4 matrix);
	public:
		virtual ~Layer();
		virtual void Add(Renderable2D* renderable);
		virtual void Render();
	};
}