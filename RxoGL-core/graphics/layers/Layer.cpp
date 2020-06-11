#include "Layer.h"

namespace rxogl
{
	Layer::Layer(Renderer2D* renderer, Shader* shader, glm::mat4 matrix)
		: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(matrix)
	{
		//m_Shader->Bind();
		//m_Shader->SetUniformMat4f("pr_matrix", matrix); // Edit shader to take in projection matrix instead of entire mvp
		//m_Shader->Unbind();
	}

	Layer::~Layer()
	{
		delete m_Renderer;
		delete m_Shader;
		for (unsigned int i = 0; i < m_Renderables.size(); i++)
			delete m_Renderables[i];
	}

	void Layer::Add(Renderable2D* renderable)
	{
		m_Renderables.push_back(renderable);
	}

	void Layer::Render()
	{
		m_Shader->Bind();
		m_Renderer->Begin();
		for (const Renderable2D* renderable : m_Renderables)
			m_Renderer->Submit(renderable);
		m_Renderer->End();
		m_Renderer->Flush();
	}
}