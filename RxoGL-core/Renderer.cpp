#include "Renderer.h"
#include <iostream>
#include <gl/GLU.h>
#include "Buffer.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): "
			<< function << " " << line << std::endl;
		return false;
	}
	return true;
}

namespace rxogl
{
	void Renderer::Clear() const
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void Renderer::Draw(const VertexArray& va, const rxogl::IndexBuffer& ib, const Shader& shader) const
	{
		va.Bind();
		ib.Bind();
		shader.Bind();

		GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

	}
}