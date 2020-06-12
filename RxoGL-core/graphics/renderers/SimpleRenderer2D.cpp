#include "SimpleRenderer2D.h"

namespace rxogl
{
	void SimpleRenderer2D::Submit(const Renderable2D* renderable)
	{
		m_RenderQueue.push_back((StaticSprite*) renderable);
	}

	void SimpleRenderer2D::Flush()
	{
		while (!m_RenderQueue.empty())
		{
			const StaticSprite* sprite = m_RenderQueue.front();
			sprite->GetVAO()->Bind();
			sprite->GetIBO()->Bind();
			sprite->GetShader().Bind();

			glm::mat4 proj = glm::ortho(0.f, 960.f, 0.f, 540.f, -1.0f, 1.0f);
			glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(/*-10*/0, 0, 0));
			glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(sprite->GetPosition()));
			glm::mat4 mvp = proj * view * model;

			sprite->GetShader().SetUniformMat4f("u_MVP", mvp);
			GLCall(glDrawElements(GL_TRIANGLES, sprite->GetIBO()->GetCount(), GL_UNSIGNED_INT, nullptr));

			sprite->GetIBO()->Unbind();
			sprite->GetVAO()->Unbind();

			m_RenderQueue.pop_front();
		}
	}
}