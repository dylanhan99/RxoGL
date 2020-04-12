#include "graphics/window.h"

int main()
{
	using namespace rxogl;
	using namespace graphics;

	Window window("rxogl", 960, 540);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	std::cout << glGetString(GL_VERSION) << std::endl;

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	while (!window.closed())
	{
		window.clear();
		if (window.isKeyPressed(GLFW_KEY_A))
		{
			std::cout << "Pressed A" << std::endl;
		}		
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			std::cout << "LEFT" << std::endl;
		}
		double x, y;
		window.getMousePosition(x, y);
		std::cout << x << "," << y << std::endl;
#if 0
		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
#else
		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f( 0.5f, 0.5f);
		glVertex2f( 0.5f, -0.5f);
		glEnd();
#endif
		window.update();
	}

	return 0;
}