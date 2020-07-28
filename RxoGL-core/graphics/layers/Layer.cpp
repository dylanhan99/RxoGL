#include "Layer.h"

namespace rxogl
{
	Layer::Layer(std::shared_ptr<Renderer2D> renderer, std::shared_ptr<Shader> shader, glm::mat4 matrix)
		: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(matrix)
	{

	}

	Layer::~Layer()
	{
		//delete m_Renderer;
		//delete m_Shader;
		for (unsigned int i = 0; i < m_Renderables.size(); i++)
			delete m_Renderables[i];
	}

	void Layer::Add(ecs::Entity2D* renderable)
	{
		m_Renderables.push_back(renderable);
	}

	void Layer::Render()
	{
		m_Shader->Bind();
		m_Renderer->Begin();
		int i = 0;
		for (const ecs::Entity2D* renderable : m_Renderables)
		{
			renderable->Submit(m_Renderer);
		}
		m_Renderer->End();
		m_Renderer->Flush();
	}
}