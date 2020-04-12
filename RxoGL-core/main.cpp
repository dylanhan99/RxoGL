#include "window.h"

int main()
{
	using namespace rxogl;
	using namespace graphics;

	Window window("rxogl", 960, 1040);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	std::cout << glGetString(GL_VERSION) << std::endl;

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	while (!window.closed())
	{
		window.clear();
		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f( 0.5f, 0.5f);
		glVertex2f( 0.5f, -0.5f);
		glEnd();
		window.update();
	}

	return 0;
}