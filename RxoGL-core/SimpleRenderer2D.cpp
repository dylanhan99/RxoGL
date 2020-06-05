#include "SimpleRenderer2D.h"

namespace rxogl
{
	void SimpleRenderer2D::Submit(Renderable2D* renderable)
	{
		m_RenderQueue.push_back(*renderable);
	}

	void SimpleRenderer2D::Flush()
	{
		while (!m_RenderQueue.empty())
		{
			const Renderable2D& renderable = m_RenderQueue.front();
			renderable.GetVAO()->Bind();
			renderable.GetIBO()->Bind();
			renderable.GetShader().Bind();

			glm::mat4 proj = glm::ortho(0.f, 960.f, 0.f, 540.f, -1.0f, 1.0f);
			glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(/*-10*/0, 0, 0));
			glm::mat4 model = glm::translate(glm::mat4(1.0f), renderable.GetPosition());
			glm::mat4 mvp = proj * view * model;

			renderable.GetShader().SetUniformMat4f("u_MVP", mvp);
			GLCall(glDrawElements(GL_TRIANGLES, renderable.GetIBO()->GetCount(), GL_UNSIGNED_INT, nullptr));

			renderable.GetIBO()->Unbind();
			renderable.GetVAO()->Unbind();

			m_RenderQueue.pop_front();
		}
	}
}