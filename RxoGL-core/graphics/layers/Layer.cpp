#include "Layer.h"
#include "../shader.h"
#include "../renderers/Renderer2D.h"
//#include "../renderables/Entity2D.h"

namespace rxogl
{
	Layer::Layer(std::shared_ptr<Renderer2D> renderer, std::shared_ptr<Shader> shader, glm::mat4 matrix)
		: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(matrix)
	{

	}

	Layer::~Layer()
	{
		//for (unsigned int i = 0; i < m_Renderables.size(); i++)
		//	delete m_Renderables[i];
	}

	void Layer::Add(ecs::Entity* entity)
	{
		entity->m_Layer = this;
		m_EntityManager.AddEntity(entity);// = *entity;
		//m_Renderables.push_back(entity);
	}

	void Layer::Render()
	{
		m_Shader->Bind();
		m_Renderer->Begin();
		//for (const auto* entity : m_Renderables)
		//{
		//	entity->Submit(m_Renderer);
		//}
		m_EntityManager.Update();
		m_EntityManager.Draw();
		m_Renderer->End();
		m_Renderer->Flush();
	}
}