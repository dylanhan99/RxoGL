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
		m_EntityManager.AddEntity(entity)->m_Layer = this;
	}

	void Layer::Update(float deltatime)
	{
		m_EntityManager.Update(deltatime);
	}

	void Layer::Render()
	{
		m_Shader->Bind();
		m_Renderer->Begin();
		m_EntityManager.Draw();
		m_Renderer->End();
		m_Renderer->Flush();
	}
}