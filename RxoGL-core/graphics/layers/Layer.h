#pragma once
//#include "../renderers/Renderer2D.h"
#include "../renderables/Entity2D.h"

namespace rxogl
{
	class Layer
	{
	protected:
		std::shared_ptr<Renderer2D> m_Renderer;
		std::shared_ptr<Shader> m_Shader;
		std::vector<ecs::Entity2D*> m_Renderables;
		glm::mat4 m_ProjectionMatrix;

		Layer(std::shared_ptr<Renderer2D> renderer, std::shared_ptr<Shader> shader, glm::mat4 matrix);
	public:
		virtual ~Layer();
		virtual void Add(ecs::Entity2D* renderable);
		virtual void Render();

		inline const std::shared_ptr<Shader> GetShader() const { return m_Shader; }
	};
}